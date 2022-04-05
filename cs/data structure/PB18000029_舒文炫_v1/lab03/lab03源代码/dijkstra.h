#include<stdio.h>
#include"graph.h"
#include"config.h"
#include <time.h>
#include"queueop.h"

int naiveshortestPath(ALGraph *G,int v0,int v1);
int bettershortestPath(ALGraph *G,int v0,int v1);

int naiveshortestPath(ALGraph *G,int v0,int v1){
int w=v0;
int i,vex1,findflag;
double start_time,finish_time;
my_queue* q;
int* d;

int* vfinal = (int*)malloc((G->vexnum + 1) * sizeof(int));//判断结点v是否已经被使用了，使用了为1，没使用为0
d=(int*)malloc((G->vexnum+1)*sizeof(int));//该顶点在该条路径上的前一个顶点，用来反向输出路径
path temp_path;
path* pa = (path*)malloc((G->vexnum + 1) * sizeof(path));//该顶点是否在路径上
ArcNode* pt;
start_time=clock();
q=initqueue(G->vexnum);
for(i=0;i<G->vexnum+1;i++){//初始化
    vfinal[i]=0;
    pa[i].vex=i;
    pa[i].length=-1;
    d[i]=-1;
}
pa[v0].length=0;
vfinal[v0]=1;
for(i=0;i<G->vexnum;i++){
    pt=G->vertices[w].firstarc;
    while(pt){
        if(pa[pt->adjvex].length < 0||(pa[pt->adjvex].length > pa[w].length + pt->info)){//如果下一个结点还没加入，或者到下一个结点长度比当前路径长
            d[pt->adjvex]=w;//更改到pt->adjvex的最小路径
            pa[pt->adjvex].length=pa[w].length+pt->info;//更新最小路径值
            q=enqueue(q,pa[pt->adjvex]);//更改的结点加入优先队列
            //printqueue(q);

        }
        pt=pt->nextarc;//去看与w相连的下一个顶点
    }
    if(dequeue(q,&temp_path)!=-1){//将距离最小的出队列
    //printqueue(q);
    w=temp_path.vex;
    vfinal[w]=1;//结点被使用
    if(w==v1){
        findflag=1;
        finish_time=clock();
        break;
    }
    }
    else{
        findflag=0;
        finish_time=clock();
        printf("the path does not exist!\n");
        break;
        }

}
 printf("the time consumed is %lf s\n",(double)(finish_time-start_time)/CLOCKS_PER_SEC);
if(findflag){

    printf("the length of the path is %d\n",pa[v1].length);
    printf("the path is below\n");
    vex1=v1;
    while(vex1!=v0){
        printf("%d<-",vex1);
        vex1=d[vex1];
    }
    printf("%d\n",vex1);
    printf("have fun for your journey!\n");

}
return 0;
}

int bettershortestPath(ALGraph *G,int v0,int v1){
int w=v0;
int i,vex1,findflag;
double start_time,finish_time;
my_queue* q;
int* d;

int* vfinal = (int*)malloc((G->vexnum + 1) * sizeof(int));//判断结点v是否已经被使用了，使用了为1，没使用为0
d=(int*)malloc((G->vexnum+1)*sizeof(int));//该顶点在该条路径上的前一个顶点，用来反向输出路径
path temp_path;
path* pa = (path*)malloc((G->vexnum + 1) * sizeof(path));//该顶点是否在路径上
ArcNode* pt;
start_time=clock();
q=initqueue(G->vexnum);
for(i=0;i<G->vexnum+1;i++){//初始化
    vfinal[i]=0;
    pa[i].vex=i;
    pa[i].length=-1;
    d[i]=-1;
}
pa[v0].length=0;
vfinal[v0]=1;
for(i=0;i<G->vexnum;i++){
    pt=G->vertices[w].firstarc;
    while(pt){
        if(pa[pt->adjvex].length < 0||(pa[pt->adjvex].length > pa[w].length + pt->info)){//如果下一个结点还没加入，或者到下一个结点长度比当前路径长
            d[pt->adjvex]=w;//更改到pt->adjvex的最小路径
            pa[pt->adjvex].length=pa[w].length+pt->info;//更新最小路径值
            q=enheapqueue(q,pa[pt->adjvex]);//更改的结点加入优先队列
            //printqueue(q);

        }
        pt=pt->nextarc;//去看与w相连的下一个顶点
    }
    if(deheapqueue(q,&temp_path)!=-1){//将距离最小的出队列
    //printqueue(q);
    w=temp_path.vex;
    vfinal[w]=1;//结点被使用
    if(w==v1){
        findflag=1;
        finish_time=clock();
        break;
    }
    }
    else{
        findflag=0;
        finish_time=clock();
        printf("the path does not exist!\n");
        break;
        }

}
 printf("the time consumed is %lf s\n",(double)(finish_time-start_time)/CLOCKS_PER_SEC);
if(findflag){

    printf("the length of the path is %d\n",pa[v1].length);
    printf("the path is below\n");
    vex1=v1;
    while(vex1!=v0){
        printf("%d<-",vex1);
        vex1=d[vex1];
    }
    printf("%d\n",vex1);
    printf("have fun for your journey!\n");

}
return 0;

}
