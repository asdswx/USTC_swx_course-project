
import numpy as np
import math
import torch

device1 = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

def sigmoid(x):
    return 1.0/(1+torch.exp(-x))
def softmax(x):
    
    return(torch.exp(x)/sum(torch.exp(x)))
def cross_entrophy(x,y):
    soft_x=softmax(x)
    print(torch.log(soft_x))
    print(y)
    print(torch.log(soft_x)*y)
    return(-torch.sum(torch.log(soft_x)*y)/len(y))

a=torch.tensor([[1.0,2.0],[2.0,3.0],[3.0,4.0]],device=device1)
print(a)
c=torch.tensor([[1.0,2.0],[3.0,4.0]],device=device1)
print(c)
print(torch.matmul(a,c))
b=torch.tensor([1.0,1.0],device=device1)
print(b)
d=torch.matmul(a,c)+b
e=softmax(d)
print(torch.matmul(a,c)+b)
print(e.t())
