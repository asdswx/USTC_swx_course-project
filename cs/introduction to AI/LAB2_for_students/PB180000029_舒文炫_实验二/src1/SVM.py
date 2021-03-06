from typing import Counter
import numpy as np
import cvxopt #用于求解线性规划
from process_data import load_and_process_data
from evaluation import get_micro_F1,get_macro_F1,get_acc


#根据指定类别main_class生成1/-1标签
def svm_label(labels,main_class):
    new_label=[]
    for i in range(len(labels)):
        if labels[i]==main_class:
            new_label.append(1)
        else:
            new_label.append(-1)
    return np.array(new_label)

# 实现线性回归
class SupportVectorMachine:

    '''参数初始化 
    lr: 梯度更新的学习率
    Lambda: L2范数的系数
    epochs: 更新迭代的次数
    '''
    def __init__(self,kernel,C,Epsilon):
        self.kernel=kernel
        self.C = C
        self.Epsilon=Epsilon

    '''KERNEL用于计算两个样本x1,x2的核函数'''
    def KERNEL(self, x1, x2, kernel='Gauss', d=2, sigma=1):
        #d是多项式核的次数,sigma为Gauss核的参数
        K = 0
        if kernel == 'Gauss':
            K = np.exp(-(np.sum((x1 - x2) ** 2)) / (2 * sigma ** 2))
        elif kernel == 'Linear':
            K = np.dot(x1,x2)
        elif kernel == 'Poly':
            K = np.dot(x1,x2) ** d
        else:
            print('No support for this kernel')
        return K

    '''
    根据训练数据train_data,train_label（均为np数组）求解svm,并对test_data进行预测,返回预测分数，即svm使用符号函数sign之前的值
    train_data的shape=(train_num,train_dim),train_label的shape=(train_num,) train_num为训练数据的数目，train_dim为样本维度
    预测结果的数据类型应为np数组，shape=(test_num,1) test_num为测试数据的数目
    '''
    def fit(self,train_data,train_label,test_data):
        K=np.array([0.0 for x in range(len(train_data[:,0])*len(train_data[:,0]))])
        K=K.reshape(-1,len(train_data[:,0]))
        K1=np.array([0.0 for x in range(len(train_data[:,0])*len(train_data[:,0]))])
        K1=K1.reshape(len(train_data[:,0]),len(train_data[:,0]))
        
        for i in range(len(train_data[:,0])):
            for j in range(len(train_data[:,0])):
                K1[i,j]=self.KERNEL(train_data[i,:],train_data[j,:],kernel=self.kernel)
                K[i,j]=train_label[i]*train_label[j]*K1[i,j]

                
                
        p=np.array([-1.0 for x in range(len(train_data[:,0]))])
        G=np.array([0.0 for x in range(2*len(train_data[:,0])*len(train_data[:,0]))])
        G=G.reshape(2*len(train_data[:,0]),len(train_data[:,0]))
        h=np.array([0.0 for x in range(2*len(train_data[:,0]))])
        A=train_label.flatten()
        b=0
        
        for i in range(len(train_data[:,0])):
            G[i,i]=-1.0
            G[i+len(train_data[:,0]),i]=1.0
            h[i]=0.0
            h[i+len(train_data[:,0])]=float(self.C)
        
        K=cvxopt.matrix(K,(len(train_data[:,0]),len(train_data[:,0])),'d')
        b=cvxopt.matrix(b,(1,1),'d')
        p=cvxopt.matrix(p,(len(train_data[:,0]),1),'d')
        G=cvxopt.matrix(G,(2*len(train_data[:,0]),len(train_data[:,0])),'d')
        h=cvxopt.matrix(h,(2*len(train_data[:,0]),1),'d')
        A=cvxopt.matrix(A,(1,len(train_data[:,0])),'d')



        sol=cvxopt.solvers.qp(K,p,G,h,A,b)
        for i in range(len(train_data[:,0])):
            if(sol['x'][i]<self.Epsilon):
                sol['x'][i]=0
            if(sol['x'][i]>self.C-self.Epsilon):
                sol['x'][i]=1


        b=0.0
        qwq=np.array([0.0 for x in range(len(train_label))])
        for i in range(len(train_label)):
            qwq[i]=train_label[i]*sol['x'][i]
        count=0
        for i in range(len(train_data[:,0])):
            if(sol['x'][i]>0 and sol['x'][i]<self.C):
                count=count+1
                b=b+train_label[i]-np.dot(qwq,K1[:,i])
        b=b/count
        K2=np.array([0.0 for x in range(len(train_data[:,0])*len(test_data[:,0]))])
        K2=K2.reshape(len(train_data[:,0]),-1)
        for i in range(len(train_data[:,0])):
            for j in range(len(test_data[:,0])):
                K2[i,j]=self.KERNEL(train_data[i,:],test_data[j,:],kernel=self.kernel)
        result=np.dot(qwq,K2)+b
        
        result=result.reshape(-1,1)

        return result










def main():
    # 加载训练集和测试集
    Train_data,Train_label,Test_data,Test_label=load_and_process_data()
    Train_label=[label[0] for label in Train_label]
    Test_label=[label[0] for label in Test_label]
    train_data=np.array(Train_data)
    test_data=np.array(Test_data)
    test_label=np.array(Test_label).reshape(-1,1)
    #类别个数
    num_class=len(set(Train_label))


    #kernel为核函数类型，可能的类型有'Linear'/'Poly'/'Gauss'
    #C为软间隔参数；
    #Epsilon为拉格朗日乘子阈值，低于此阈值时将该乘子设置为0
    kernel='Poly' 
    C = 1
    Epsilon=10e-5
    #生成SVM分类器
    SVM=SupportVectorMachine(kernel,C,Epsilon)

    predictions = []
    #one-vs-all方法训练num_class个二分类器
    for k in range(1,num_class+1):
        #将第k类样本label置为1，其余类别置为-1
        train_label=svm_label(Train_label,k)
        # 训练模型，并得到测试集上的预测结果
        prediction=SVM.fit(train_data,train_label,test_data)
        predictions.append(prediction)
    predictions=np.array(predictions)
    #one-vs-all, 最终分类结果选择最大score对应的类别
    pred=np.argmax(predictions,axis=0)+1
    # 计算准确率Acc及多分类的F1-score
    print("Acc: "+str(get_acc(test_label,pred)))
    print("macro-F1: "+str(get_macro_F1(test_label,pred)))
    print("micro-F1: "+str(get_micro_F1(test_label,pred)))


main()
