#include"fileop.h"
#include<malloc.h>
#include"graph.h"

ALGraph* Create_Graph();//创建图
ArcNode* create_node(int a,int b);//创建结点
int insert_node(ALGraph* G,int i,ArcNode* p);//将弧结点插入到图中
int Print_Graph(ALGraph* G);//打印图
int turnbitfile(ALGraph* G);//将图转为二进制文件
ALGraph* Create_Graph_by_compress();//通过压缩后文件创建图

ArcNode* create_node(int a,int b){
    ArcNode* p;
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=a;
    p->info=b;
    p->nextarc=NULL;
    return p;
}
int insert_node(ALGraph* G,int i,ArcNode* p){//头插
    p->nextarc=G->vertices[i].firstarc;
    G->vertices[i].firstarc=p;
    return 0;
}





ALGraph* Create_Graph(){
int vexnum,arcnum,vex1;
ALGraph* G;
int buffer[3];
int i=0;
ArcNode* p;
FILE* fp;
G=(ALGraph*)malloc(sizeof(ALGraph));
fp=fopen(usedbitfile,"rb");
if(fp==NULL){
    printf("file does not exist,please create it first\n");
    exit(-1);
}
fread(&vexnum,sizeof(int),1,fp);
G->vexnum=vexnum;
G->vertices=(AdjList)malloc((vexnum+1)*sizeof(VNode));
for(i=0;i<=vexnum;i++)
    G->vertices[i].firstarc=NULL;
while(1){//read the file to get the graph
    fread(buffer,sizeof(int),3,fp);
    if(feof(fp))
        break;
    p=create_node(buffer[1],buffer[2]);
    insert_node(G,buffer[0],p);
    arcnum++;
}
G->arcnum=arcnum;
fclose(fp);
return G;

}

int Print_Graph(ALGraph* G){
int i;
ArcNode* p;
for(i=1;i<=G->vexnum;i++){
    printf("%d",i);
    for(p=G->vertices[i].firstarc;p;p=p->nextarc)
        printf("->%d %d|",p->adjvex,p->info);
    printf("\n");
}

}

int turnbitfile(ALGraph* G){
FILE* fp;
int i,j,k;
int* arcarray;
ArcNode* p;
fp=fopen(cpedbitfile,"wb");
if(fp==NULL){
    printf("failed\n");
    exit(-1);
}
arcarray=(int*)malloc((G->vexnum+1)*sizeof(int));
arcarray[0]=0;
for(i=1;i<=G->vexnum;i++){
    j=0;
    p=G->vertices[i].firstarc;
    while(p){
        j++;
        p=p->nextarc;
    }
    arcarray[i]=j;
}
fwrite(&G->vexnum,sizeof(int),1,fp);
fwrite(arcarray,sizeof(int),G->vexnum+1,fp);
for(i=1;i<=G->vexnum;i++){
    p=G->vertices[i].firstarc;
    while(p){
        fwrite(&p->adjvex,sizeof(int),1,fp);
        fwrite(&p->info,sizeof(int),1,fp);
        p=p->nextarc;
    }
}
fclose(fp);
return 0;
}

ALGraph* Create_Graph_by_compress(){
FILE* fp;
int vexnum,arcnum,vex1;
int adj,info;
int* arcarray;
ALGraph* G;
int i=0,j;
ArcNode* p;
G=(ALGraph*)malloc(sizeof(ALGraph));
fp=fopen(cpedbitfile,"rb");
if(fp==NULL){
    printf("file does not exist,please create it first\n");
    exit(-1);
}
fread(&vexnum,sizeof(int),1,fp);
G->vexnum=vexnum;
G->vertices=(AdjList)malloc((vexnum+1)*sizeof(VNode));
arcarray=(int*)malloc((vexnum+1)*sizeof(int));
fread(arcarray,sizeof(int),vexnum+1,fp);
for(i=0;i<=vexnum;i++)
    G->vertices[i].firstarc=NULL;
for(i=1;i<=vexnum;i++){
    for(j=0;j<arcarray[i];j++){
        fread(&adj,sizeof(int),1,fp);
        fread(&info,sizeof(int),1,fp);
        p=create_node(adj,info);
        insert_node(G,i,p);
        arcnum++;
    }
}
G->arcnum=arcnum;
fclose(fp);
return G;
}
