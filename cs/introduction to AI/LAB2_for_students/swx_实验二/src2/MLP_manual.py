import torch
import numpy as np
import torch.autograd
import math
import matplotlib.pyplot as plt
from collections import Counter
device1 = torch.device("cuda" if torch.cuda.is_available() else "cpu")

def sigmoid(x):
    return 1.0/(1+torch.exp(-x))
def softmax(x):
    
    return(torch.exp(x)/sum(torch.exp(x)))
def cross_entrophy(x,y):
    return(-torch.log(x[int(y)-1]))
def loss(x,y):
    sumloss=0.0
    for i in range(len(y)):
        sumloss=sumloss+cross_entrophy(x[:,i],y[i])

    sumloss=sumloss/len(y)

    return sumloss







class mlpmodel():
    def __init__(self,hidden,outlayer,iterations=1000,lrate=0.001):
        self.hidden=hidden
        self.iterations=iterations
        self.lrate=lrate
        self.outlayer=outlayer


    def _initweight_(self,x,y):
        feature_nx,sample_n=x.shape
        feature_ny=self.outlayer
        self.W0=torch.randn(self.hidden,feature_nx,device=device1,requires_grad=True)
        self.w0=torch.randn(self.hidden,1,device=device1,requires_grad=True)
        self.W1=torch.randn(self.hidden,self.hidden,device=device1,requires_grad=True)
        self.w1=torch.randn(self.hidden,1,device=device1,requires_grad=True)
        self.W2=torch.randn(feature_ny,self.hidden,device=device1,requires_grad=True)
        self.w2=torch.randn(feature_ny,1,device=device1,requires_grad=True)


    def forward(self,x,y):
        input1=torch.matmul(self.W0,x)+self.w0
        output1=sigmoid(input1)
        input2=torch.matmul(self.W1,output1)+self.w1
        output2=sigmoid(input2)
        input3=torch.matmul(self.W2,output2)+self.w2
        output3=softmax(input3)
        cost=loss(output3,y)
        return output1,output2,output3,cost

    def backward(self,x,y,output1,output2,output3,cost):
        
        feature_ny=self.outlayer
        dfy=torch.zeros(feature_ny,len(y),device=device1)
        one1=torch.ones(1,len(y),device=device1)
        for i in range(len(y)):
            for j in range(feature_ny):
                if(j==y[i]-1):
                    dfy[int(y[i])-1,i]=output3[int(y[i])-1,i]-1.0
                else:
                    dfy[j,i]=0
        dw2=torch.matmul(dfy,one1.t())/len(y)    
        dW2=torch.matmul(dfy,output2.t())/len(y) 
        ds1=torch.zeros(self.hidden,len(y),device=device1)
        ds0=torch.zeros(self.hidden,len(y),device=device1)
        for i in range(len(y)):
            for j in range(self.hidden):
                ds1[j,i]=output2[j,i]*(1.0-output2[j,i])
                ds0[j,i]=output1[j,i]*(1.0-output1[j,i])
        dhi1=torch.mul(torch.matmul(self.W2.t(),dfy),ds1)
        dW1=torch.matmul(dhi1,output1.t())/len(y) 
        dw1=torch.matmul(dhi1,one1.t())/len(y) 
        dW0=torch.matmul(torch.mul(torch.matmul(self.W1.t(),dhi1),ds0),x.t())/len(y) 
        dw0=torch.matmul(torch.mul(torch.matmul(self.W1.t(),dhi1),ds0),one1.t())/len(y) 
        cost.backward()
        print(self.W2.grad)
        print(dW2)
        print(self.W1.grad)
        print(dW1)
        print(self.W0.grad)
        print(dW0)
        print(self.w2.grad)
        print(dw2)
        print(self.w1.grad)
        print(dw1)
        print(self.w0.grad)
        print(dw0)
        self.W2.data=self.W2.data-self.lrate*dW2.data
        self.W1.data=self.W1.data-self.lrate*dW1.data
        self.W0.data=self.W0.data-self.lrate*dW0.data
        self.w2.data=self.w2.data-self.lrate*dw2.data
        self.w1.data=self.w1.data-self.lrate*dw1.data
        self.w0.data=self.w0.data-self.lrate*dw0.data
        '''

        cost.backward()
        dW2=self.W2.grad
        dW1=self.W1.grad
        dW0=self.W0.grad
        dw1=self.w1.grad
        dw2=self.w2.grad
        dw0=self.w0.grad
        self.W2.data=self.W2.data-self.lrate*dW2.data
        self.W1.data=self.W1.data-self.lrate*dW1.data
        self.W0.data=self.W0.data-self.lrate*dW0.data
        self.w2.data=self.w2.data-self.lrate*dw2.data
        self.w1.data=self.w1.data-self.lrate*dw1.data
        self.w0.data=self.w0.data-self.lrate*dw0.data
        '''






    
    
    def fit(self,x,y):

        self._initweight_(x,y)
        num=[]
        costlist=[]
        for i in range(self.iterations):
            output1,output2,output3,cost=self.forward(x,y)
            costlist.append(cost)
            num.append(i+1)
            self.backward(x,y,output1,output2,output3,cost)
        plt.plot(num, np.squeeze(np.array(costlist)))
        plt.xlim((1, 1500))
        plt.ylim(0, 2)
        plt.xlabel('iterate_nums')
        plt.ylabel('costvalue')
        plt.savefig('G:\绸带\LAB2_for_students\src2')
        plt.show()

    

if __name__=='__main__':
        x=torch.randn(100,5,device=device1)
        k=torch.rand(100,1,device=device1)
        y=torch.zeros(100,1,device=device1)
        for i in range(len(k)):
            if(k[i]<=1/3):
                y[i]=1
            if(k[i]>1/3 and k[i]<=2/3):
                y[i]=2
            if(k[i]>2/3):
                y[i]=3
        qwq=mlpmodel(hidden=4,outlayer=3)
        qwq.fit(x.t(),y)
        _,__,output,____=qwq.forward(x.t(),y)
        pred=np.array([0 for x in range(len(y))])
        pred=torch.argmax(output.t(),dim=1).cpu().numpy()+1
        sum=0
        for i in range(len(y)):
            if(pred[i]==int(y[i])):
                sum=sum+1
        print(sum/len(y))




        








