
import math #the critical function sqrt is supported by the library
def solve(): #solve the function y=x^2-1
    a=input("please input y,press qwq to exit:")
    while a!='qwq':
        if float(a)<-1:
            print("no root\n")
        elif float(a)==-1:
            print("the root is 0\n")
        else:
            print("the root is {},{}".format(math.sqrt(float(a)+1),-math.sqrt(float(a)+1)))
        a=input("please input y:")
'''
above is a while circulaar body
qwq is the symbol to terminate the function
  a<-1 no root
  a=-1 x=0
  a>-1 two different roots
'''        
solve()