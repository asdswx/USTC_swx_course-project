

import numpy as np
import math
import time 

#my method

def integrate1(start,end,i):
    x=np.linspace(start,end,10000)
    y=np.sqrt(i+x**2)
    dx=x[1]-x[0]
    s=np.sum(y*dx)
    return s
'''
the function above is used to calculate the integral of sqrt(i+x**2)
From numpy, we can generate an array, which is used to divide the integral domain equally into small intervals. I set the length 10000
y is the array of the value of sqrt(i+x**2) at the endpoint of the intervals
dx is the length of the small interval.
we add y*dx to get the reault.
This is the traditional way of Riemman integral.
'''
x=np.linspace(0,1,10000)      #the same division
res=0

for i in x:
    res=res+integrate1(-i,i,i)# for each i, we get the value of integral(sqrt(i+x^2)) from -i to i
res=res/10000                 #the Riemman sum
print("the result is {}\n".format(res))

#scipy method

from scipy import integrate
def f(y,x):                   #the integrand, the order of the variable is the order of integral. In this situation, we put y first.
    return math.sqrt(x+y**2)
def boundx():                 #the integrating interval of x
    return [0,1]
def boundy(x):                #the integrating interval of y
    return [-x,x]
v,err=integrate.nquad(f,[boundy,boundx]) #v is the value, err is the error.
print("the result is {}\n".format(v))

'''
This part is to compare the efficiency of my method and scipy method
we get the time comsumesd in each method after given times
'''
d=input("the times you want:")
#my method
start=time.perf_counter()#start time
for k in range(int(d)):#we execute the coda block for d times
    x=np.linspace(0,1,10000)
    res=0
    for i in x:
        res=res+integrate1(-i,i,i)
    res=res/10000
        
end=time.perf_counter()#end time
print("the time comsumed through my method is {}\n".format(end-start))#the total time used

#scipy method
start1=time.perf_counter()
for k in range(int(d)):
    v,err=integrate.nquad(f,[boundy,boundx])
end1=time.perf_counter()
print("the time comsumed through scipy method is {}\n".format(end1-start1))




