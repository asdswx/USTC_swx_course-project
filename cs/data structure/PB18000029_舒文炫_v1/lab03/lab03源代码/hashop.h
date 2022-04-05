#include<stdio.h>

int hashfind(int* vexlist,int a);//fina a in vexlist,if not found insert it;


int hashfind(int* hashlist,int a){
int hashvalue;
hashvalue=(a+7857649)%40000000;
if(hashlist[hashvalue]==0){
    hashlist[hashvalue]=a;
    return 0;
    }
else{
    while(hashlist[hashvalue]!=a&&hashlist[hashvalue]!=0){
        hashvalue=(hashvalue+7860767)%40000000;
    }
    if(hashlist[hashvalue]==a)
        return 1;
    else{
        hashlist[hashvalue]=a;
        return 0;
    }
}
}
