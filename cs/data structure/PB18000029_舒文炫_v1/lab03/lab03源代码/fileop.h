#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include"config.h"
#include"hashop.h"
int preprocfile();//预处理原文件
int procbitfile();//处理原二进制文件
int countfilevex();//数文件中顶点的个数

int preprocfile(){
FILE *fp1,*fp2;
int i,count1=0;
char src[20],dst[20],distance[20];
int buffer1[3];
char filename[100];
printf("input the filename\n");
scanf("%s",filename);
fp1=fopen(filename,"r");
fp2=fopen(rawbitfile,"wb");
if(fp1==NULL||fp2==NULL){
     printf("\nCannot open file!");
     exit(-1);
}
while(!feof(fp1)){//每次读出三个整型数，分别是源点，目的点，距离，将其按照二进制写入既定文件
    fscanf(fp1,"%s%s%s",src,dst,distance);
    buffer1[0]=atoi(src);
    buffer1[1]=atoi(dst);
    buffer1[2]=atoi(distance);
    fwrite(buffer1,sizeof(int),3,fp2);
    count1++;
}
printf("--%d\n",count1);
fclose(fp1);
fclose(fp2);
return 0;
}

int procbitfile(){
FILE *fp,*fp1;
int maxvex=0;
int i;
int buffer[3];
fp=fopen(rawbitfile,"rb");
fp1=fopen(usedbitfile,"wb");
if(fp==NULL||fp1==NULL){
    printf("file does not exist,please create it first\n");
    exit(-1);
}
while(1){//这一部分主要是看数值最大的顶点是多少，这个就是创建图的顶点数
    fread(buffer,sizeof(int),3,fp);
    if(feof(fp))
        break;
    if(maxvex<buffer[0])
        maxvex=buffer[0];
    if(maxvex<buffer[1])
        maxvex=buffer[1];
}

rewind(fp);
fwrite(&maxvex,sizeof(int),1,fp1);
while(1){
    fread(buffer,sizeof(int),3,fp);
    if(feof(fp))
        break;
    fwrite(buffer,sizeof(int),3,fp1);
}
fclose(fp);
fclose(fp1);
return 0;
}

int countfilevex(){
FILE *fp;
int vexnum=0;
int* vexlist;
int* hashlist;
int buffer[3];
vexlist=(int*)malloc(30000000*sizeof(int));
memset(vexlist,0,30000000);
hashlist=(int*)malloc(40000000*sizeof(int));
memset(vexlist,0,40000000);
fp=fopen(rawbitfile,"rb");
if(fp==NULL){
    printf("file does not exist,please create it first\n");
    exit(-1);
}
while(1){//使用哈希查找，快速统计出有多少个顶点
    fread(buffer,sizeof(int),3,fp);
    if(feof(fp))
        break;
    if(!hashfind(hashlist,buffer[0])){
        vexlist[vexnum]=buffer[0];
        vexnum++;
    }

    if(!hashfind(hashlist,buffer[1])){
        vexlist[vexnum]=buffer[1];
        vexnum++;
    }
}
fclose(fp);
printf("the vexnum is %d\n",vexnum);
return 0;
}
