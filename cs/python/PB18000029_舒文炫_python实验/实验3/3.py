import numpy as np
import math 

class Quaternion: 
    '''
    in init part, the parameter a,b,c,d shows the quaternion a+bi+cj+dk saved in the way of quanum vector.
    self.angle is the Eular angle of the quaternion. 
    '''
    def __init__(self, a, b, c, d):
        self.quanum = np.array([a, b, c, d])
        self.angle=np.array([0,0,0])
    '''
    In this part, printq print the quaternion in the style: a+bi+cj+dk. Printa print the quaternion in the style:(alpha,beta,gamma)
    '''
    def printq(self):
        symbol = [" ", "i ", "j ", "k"]
        q = self.quanum.copy()
        result = ""
        for i in range(3):
            if q[i]>1e-4 or q[i]<-1e-4:
                result = result + str(round(q[i], 4)) + symbol[i]
            if q[i+1] > 1e-4:
                result=result+"+"
        if(q[3]>1e-4 or q[3]<-1e-4):
            result = result + str(round(q[3], 4)) + symbol[3]
        if result == "":
            return "0"
        else:
            return result
    def printa(self):
        a=self.angle.copy()
        result="("
        for i in range(3):
                result = result + str(round(a[i], 4)) + ","
        result=result[0:-1]
        result=result+")"
        if result =="()":
            return "0"
        else:
            return result
            

    '''
    the addition of quaternion
    '''
    def add(self, x):
        q = self.quanum.copy()
        q=q+x.quanum
        return Quaternion(q[0], q[1], q[2], q[3])
    '''
    the subtraction of quaternion
    '''
    def sub(self, x):
        q = self.quanum.copy()
        q=q-x.quanum
        return Quaternion(q[0], q[1], q[2], q[3])
    '''
    the multiplication of quaternion
    '''
    def mul(self, x):
        q = self.quanum.copy()
        p = x.quanum.copy()
        a = q[0]*p[0] - q[1]*p[1] - q[2]*p[2] - q[3]*p[3]
        b = q[0]*p[1] + q[1]*p[0] + q[2]*p[3] - q[3]*p[2]
        c = q[0]*p[2] - q[1]*p[3] + q[2]*p[0] + q[3]*p[1]
        d = q[0]*p[3] + q[1]*p[2] - q[2]*p[1] + q[3]*p[0]
        return Quaternion(a, b, c, d)
    '''
    the square of mod of quaternion
    '''
    
    def modpow(self):
        q = self.quanum.copy()
        return np.sum(q*q)
    '''
    the inverse of quaternion
    '''
    def inverse(self):
        q = self.quanum.copy()
        mod = self.modpow()
        q=q/mod
        return Quaternion(q[0], -q[1], -q[2], -q[3])
    '''
    the division of quaternion
    '''
    def divide(self, x):
        result = self.mul(x.inverse())
        return result
    '''
    transform quaternion to eular angle
    '''
    def qua2eular(self):
        q=self.quanum.copy()
        mod=math.pow(self.modpow(),0.5)
        q=q/mod
        alpha=math.atan2(2*(q[0]*q[1]+q[2]*q[3]),1-2*(q[1]**2+q[2]**2))
        beta=math.asin(2*(q[0]*q[2]-q[1]*q[3]))
        gamma=math.atan2(2*(q[0]*q[3]+q[1]*q[2]),1-2*(q[2]**2+q[3]**2))
        alpha=alpha/math.pi*180
        beta=beta/math.pi*180
        gamma=gamma/math.pi*180
        angle=np.array([alpha,beta,gamma])
        self.angle=angle
    '''
    transform eular angle to quaternion
    '''
def eular2qua(alpha,beta,gamma):
    q=np.array([0.0 for x in range(4)])
    q[0]=math.cos(alpha/2)*math.cos(beta/2)*math.cos(gamma/2)+math.sin(alpha/2)*math.sin(beta/2)*math.sin(gamma/2)
    q[1]=math.sin(alpha/2)*math.cos(beta/2)*math.cos(gamma/2)-math.cos(alpha/2)*math.sin(beta/2)*math.sin(gamma/2)
    q[2]=math.cos(alpha/2)*math.sin(beta/2)*math.cos(gamma/2)+math.sin(alpha/2)*math.cos(beta/2)*math.sin(gamma/2)
    q[3]=math.cos(alpha/2)*math.cos(beta/2)*math.sin(gamma/2)-math.sin(alpha/2)*math.sin(beta/2)*math.cos(gamma/2)
    return Quaternion(q[0], q[1], q[2], q[3])    

print("四元数计算")
print("0:结束，1：求和,2:减法，3：乘法，4：除法，5：欧拉角转四元数，6：四元数转欧拉角")
print("用法:启动时，先输入模式，再输入两个四元数，即输入8个数，会给出结果。输入角度是用角度制，按照(z,y,x)顺序输入。四元数转欧拉角是以(z,y,x)轴顺序给出")
print("输入模式")
mode=int(input())
while(mode!=0):
    if(mode in [1,2,3,4,5]):
        a=np.array([0.0 for x in range(4)])
        b=np.array([0.0 for x in range(4)])
        print("输入第一个四元数")
        for i in range(4):
            a[i]=float(input())
        print("输入第二个四元数")
        for i in range(4):
            b[i]=float(input())

        a=Quaternion(a[0], a[1], a[2], a[3])
        b=Quaternion(b[0], b[1], b[2], b[3])
        print(a.printq())
        print(b.printq())


        if(mode==1):
            print("加法结果为"+a.add(b).printq())
        if(mode==2):
            print("减法结果为"+a.sub(b).printq())
        if(mode==3):
            print("乘法结果为"+a.mul(b).printq())
        if(mode==4):
            print("除法结果为"+a.divide(b).printq())
        if(mode==5):
            a.qua2eular()
            b.qua2eular()
            print("第一个四元数对应欧拉角为"+a.printa())
            print("第一个四元数对应欧拉角为"+b.printa())
    if(mode==6):
        c=np.array([0.0 for x in range(3)])
        print("输入欧拉角")
        for i in range(3):
            c[i]=float(input())/180.0*math.pi
        print("对应四元数为："+eular2qua(c[0],c[1],c[2]).printq())

    mode=int(input())

        



 
    
 


 
