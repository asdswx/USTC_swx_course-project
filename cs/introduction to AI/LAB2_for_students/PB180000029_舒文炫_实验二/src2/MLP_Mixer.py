import torch
import torch.nn as nn
import torch.utils.data
from torchvision import transforms
from torchvision.datasets import MNIST

# 禁止import除了torch以外的其他包，依赖这几个包已经可以完成实验了

device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")


class Mixer_Layer(nn.Module):
    def __init__(self, patch_size, hidden_dim):
        super(Mixer_Layer, self).__init__()
        ########################################################################
        # 这里需要写Mixer_Layer（layernorm，mlp1，mlp2，skip_connection）
        self.patch_size = patch_size
        self.hidden_dim = hidden_dim
        self.layer_norm = nn.LayerNorm(self.hidden_dim)
        self.mlp1 = nn.Sequential(
            nn.Linear(int(28/patch_size) ** 2, int(28/patch_size) ** 2),
            nn.GELU(),
            nn.Linear(int(28/patch_size) ** 2, int(28/patch_size) ** 2)
        )
        self.mlp2 = nn.Sequential(
            nn.Linear(hidden_dim, patch_size**2),
            nn.GELU(),
            nn.Linear(patch_size**2,hidden_dim)
        )
        ########################################################################

    def forward(self, x):
        ########################################################################
        output = self.layer_norm(x).transpose(1, 2)
        output = self.mlp1(output).transpose(1, 2) + x
        output = self.mlp2(self.layer_norm(output)) + output
        return output
        ########################################################################


class MLPMixer(nn.Module):
    def __init__(self, patch_size, hidden_dim, depth):
        super(MLPMixer, self).__init__()
        assert 28 % patch_size == 0, 'image_size must be divisible by patch_size'
        assert depth > 1, 'depth must be larger than 1'
        ########################################################################
        # 这里写Pre-patch Fully-connected, Global average pooling, fully connected
        self.patch_size = patch_size
        self.hidden_dim = hidden_dim
        self.patchnum=int(28/self.patch_size)**2
        self.pre_batch_full_connect = nn.Linear(28 * 28, 28 * 28)
        self.conv = nn.Linear(self.patch_size ** 2, hidden_dim)
        self.mix_layers = nn.Sequential(*[Mixer_Layer(patch_size, hidden_dim) for i in range(depth)])
        self.full_connect = nn.Linear(self.patchnum* self.hidden_dim, 10)
        ########################################################################

    def forward(self, x):
        ########################################################################
        # 注意维度的变化
        x = x.view(-1, 28 * 28)
        output = self.pre_batch_full_connect(x)
        output = self.conv(output.view(-1, self.patchnum, self.patch_size ** 2))
        output = self.mix_layers(output)
        output = output.view(-1, self.patchnum * self.hidden_dim)
        output = self.full_connect(output)
        return output
        ########################################################################


def train(model, train_loader, optimizer, n_epochs, criterion):
    model.train()
    for epoch in range(n_epochs):
        for batch_idx, (data, target) in enumerate(train_loader):
            data, target = data.to(device), target.to(device)
            ########################################################################
            # 计算loss并进行优化
            optimizer.zero_grad()
            output = model(data)
            loss = criterion(output, target)
            loss.backward()
            optimizer.step()
            ########################################################################
            if batch_idx % 100 == 0:
                print('Train Epoch: {}/{} [{}/{}]\tLoss: {:.6f}'.format(
                    epoch, n_epochs, batch_idx * len(data), len(train_loader.dataset), loss.item()))


def test(model, test_loader, criterion):
    model.eval()
    test_loss = 0.
    num_correct = 0  # correct的个数
    total = 0
    with torch.no_grad():
        for data, target in test_loader:
            data, target = data.to(device), target.to(device)
            ########################################################################
            # 需要计算测试集的loss和accuracy
            output = model(data)
            loss = criterion(output, target)
            test_loss =test_loss+ loss
            num_correct =num_correct+ (torch.argmax(output, 1) == target).sum().item()
            total =total+ len(target)
        accuracy = num_correct / total
        test_loss=test_loss*len(target)/total
        ########################################################################
        print("Test set: Average loss: {:.4f}\t Acc {:.2f}".format(test_loss, accuracy))


def main():
    n_epochs = 5
    batch_size = 128
    learning_rate = 1e-3

    transform = transforms.Compose(
        [transforms.ToTensor(),
         transforms.Normalize((0.1307,), (0.3081,))])

    trainset = MNIST(root='./data', train=True, download=True, transform=transform)
    train_loader = torch.utils.data.DataLoader(
        trainset, batch_size=batch_size, shuffle=True, num_workers=2, pin_memory=True)

    testset = MNIST(root='./data', train=False, download=True, transform=transform)
    test_loader = torch.utils.data.DataLoader(
        testset, batch_size=batch_size, shuffle=False, num_workers=2, pin_memory=True)

    ########################################################################
    model = MLPMixer(patch_size=7, hidden_dim=10, depth=4).to(device)  # 参数自己设定，其中depth必须大于1
    # 这里需要调用optimizer，criterion(交叉熵)
    optimizer = torch.optim.Adam(model.parameters(), lr=learning_rate)
    criterion = nn.CrossEntropyLoss()
    ########################################################################

    train(model, train_loader, optimizer, n_epochs, criterion)
    test(model, test_loader, criterion)


if __name__ == "__main__":
    main()
