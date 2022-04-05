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

int* vfinal = (int*)malloc((G->vexnum + 1) * sizeof(int));//�жϽ��v�Ƿ��Ѿ���ʹ���ˣ�ʹ����Ϊ1��ûʹ��Ϊ0
d=(int*)malloc((G->vexnum+1)*sizeof(int));//�ö����ڸ���·���ϵ�ǰһ�����㣬�����������·��
path temp_path;
path* pa = (path*)malloc((G->vexnum + 1) * sizeof(path));//�ö����Ƿ���·����
ArcNode* pt;
start_time=clock();
q=initqueue(G->vexnum);
for(i=0;i<G->vexnum+1;i++){//��ʼ��
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
        if(pa[pt->adjvex].length < 0||(pa[pt->adjvex].length > pa[w].length + pt->info)){//�����һ����㻹û���룬���ߵ���һ����㳤�ȱȵ�ǰ·����
            d[pt->adjvex]=w;//���ĵ�pt->adjvex����С·��
            pa[pt->adjvex].length=pa[w].length+pt->info;//������С·��ֵ
            q=enqueue(q,pa[pt->adjvex]);//���ĵĽ��������ȶ���
            //printqueue(q);

        }
        pt=pt->nextarc;//ȥ����w��������һ������
    }
    if(dequeue(q,&temp_path)!=-1){//��������С�ĳ�����
    //printqueue(q);
    w=temp_path.vex;
    vfinal[w]=1;//��㱻ʹ��
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

int* vfinal = (int*)malloc((G->vexnum + 1) * sizeof(int));//�жϽ��v�Ƿ��Ѿ���ʹ���ˣ�ʹ����Ϊ1��ûʹ��Ϊ0
d=(int*)malloc((G->vexnum+1)*sizeof(int));//�ö����ڸ���·���ϵ�ǰһ�����㣬�����������·��
path temp_path;
path* pa = (path*)malloc((G->vexnum + 1) * sizeof(path));//�ö����Ƿ���·����
ArcNode* pt;
start_time=clock();
q=initqueue(G->vexnum);
for(i=0;i<G->vexnum+1;i++){//��ʼ��
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
        if(pa[pt->adjvex].length < 0||(pa[pt->adjvex].length > pa[w].length + pt->info)){//�����һ����㻹û���룬���ߵ���һ����㳤�ȱȵ�ǰ·����
            d[pt->adjvex]=w;//���ĵ�pt->adjvex����С·��
            pa[pt->adjvex].length=pa[w].length+pt->info;//������С·��ֵ
            q=enheapqueue(q,pa[pt->adjvex]);//���ĵĽ��������ȶ���
            //printqueue(q);

        }
        pt=pt->nextarc;//ȥ����w��������һ������
    }
    if(deheapqueue(q,&temp_path)!=-1){//��������С�ĳ�����
    //printqueue(q);
    w=temp_path.vex;
    vfinal[w]=1;//��㱻ʹ��
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
