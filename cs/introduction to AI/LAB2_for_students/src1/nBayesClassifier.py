import numpy as np
import math
from collections import Counter
from process_data import load_and_process_data
from evaluation import get_micro_F1,get_macro_F1,get_acc

class NaiveBayes:
    '''参数初始化
    Pc: P(c) 每个类别c的概率分布
    Pxc: P(c|x) 每个特征的条件概率
    '''
    def __init__(self):
        self.Pc={}
        self.Pxc={}

    '''
    通过训练集计算先验概率分布p(c)和条件概率分布p(x|c)
    建议全部取log，避免相乘为0
    '''
    def fit(self,traindata,trainlabel,featuretype):
        resultc=Counter(trainlabel.flatten())
        self.Pc[1]=(resultc[1]+1)/(len(trainlabel)+3)
        self.Pc[2]=(resultc[1]+1)/(len(trainlabel)+3)
        self.Pc[3]=(resultc[1]+1)/(len(trainlabel)+3)
        for i in range(8):
            if(featuretype[i]==0):
                qwq=Counter(traindata[:,i].flatten())
                q1={}
                for key1 in self.Pc:
                    p1={}
                    for key2 in qwq:
                        p1[key2]=(sum([1 for x in range(len(trainlabel)) if trainlabel[x]==key1 and traindata[x,i]==key2])+1)/(sum([1 for x in range(len(trainlabel)) if trainlabel[x]==key1])+len(qwq))
                    q1[key1]=p1
                self.Pxc[i]=q1
            if(featuretype[i]==1):
                q1={}
                for key1 in self.Pc:
                    p1={}
                    p1["mean"]=np.sum([traindata[x,i] for x in range(len(traindata[:,i])) if trainlabel[x]==key1])/np.sum([1 for x in range(len(traindata[:,i])) if trainlabel[x]==key1])
                    p1["var"]=np.sum([pow(traindata[x,i]-p1["mean"],2) for x in range(len(traindata[:,i]))])/np.sum([1 for x in range(len(traindata[:,i])) if trainlabel[x]==key1])
                    q1[key1]=p1
                self.Pxc[i]=q1




            


    '''
    根据先验概率分布p(c)和条件概率分布p(x|c)对新样本进行预测
    返回预测结果,预测结果的数据类型应为np数组，shape=(test_num,1) test_num为测试数据的数目
    feature_type为0-1数组，表示特征的数据类型，0表示离散型，1表示连续型
    '''
    def predict(self,features,featuretype):
        pred=np.array([0 for x in range(len(features[:,0]))])

        for i in range(len(features[:,0])):
            k=0
            p1=float('-inf')
            p2=0
            for key1 in self.Pc:
                p2=math.log(self.Pc[key1],2)
                for j in range(len(featuretype)):
                    if(featuretype[j]==1):
                        p2=p2-1/2*math.log(2*math.pi*self.Pxc[j][key1]["var"],math.e)-math.pow(features[i,j]-self.Pxc[j][key1]["mean"],2)/2/self.Pxc[j][key1]["var"]
                    if(featuretype[j]==0):
                        p2=p2+math.log(self.Pxc[j][key1][features[i,j]])
                if(p2>p1):
                    k=key1
                    p1=p2
            pred[i]=k
        return(pred.reshape(-1,1))








def main():
    # 加载训练集和测试集
    train_data,train_label,test_data,test_label=load_and_process_data()
    feature_type=[0,1,1,1,1,1,1,1] #表示特征的数据类型，0表示离散型，1表示连续型

    Nayes=NaiveBayes()
    Nayes.fit(train_data,train_label,feature_type) # 在训练集上计算先验概率和条件概率

    pred=Nayes.predict(test_data,feature_type)  # 得到测试集上的预测结果

    # 计算准确率Acc及多分类的F1-score
    print("Acc: "+str(get_acc(test_label,pred)))
    print("macro-F1: "+str(get_macro_F1(test_label,pred)))
    print("micro-F1: "+str(get_micro_F1(test_label,pred)))

main()