#include"graphop.h"
#include"dijkstra.h"
int main(){
int i,flag=1,method,filetype;
int src,dst;
ALGraph* G;
printf("��ӭ���뵼��ϵͳ,����1����ԭʼ�������ļ�������0����ѹ���������ļ�\n");
scanf("%d",&filetype);
printf("���벢�����У�����ܻỨһЩʱ��......\n");
if(filetype)
    G=Create_Graph();
else
    G=Create_Graph_by_compress();
printf("�ļ�������ɣ���ͼ�Ѿ�������ȱ�µ�ͼ����Ϊ������\n");
//Print_Graph(G);
while(flag){
    printf("please input the src and dst\n");
    scanf("%d %d",&src,&dst);
    printf("input 1 for naive method, 2 for better method\n");
    scanf("%d",&method);
    printf("����Ϊ���滮·�������Ե�\n");
    if(method==1)
        naiveshortestPath(G,src,dst);
    else
        bettershortestPath(G,src,dst);
    printf("input 1 to continue,0 to finish\n");
    scanf("%d",&flag);
}

return 0;

}
