#include"graphop.h"
#include"dijkstra.h"
int main(){
int i,flag=1,method,filetype;
int src,dst;
ALGraph* G;
printf("欢迎进入导航系统,输入1读入原始二进制文件，输入0读入压缩二进制文件\n");
scanf("%d",&filetype);
printf("读入并创建中，这可能会花一些时间......\n");
if(filetype)
    G=Create_Graph();
else
    G=Create_Graph_by_compress();
printf("文件读入完成，地图已经创建，缺德地图持续为您导航\n");
//Print_Graph(G);
while(flag){
    printf("please input the src and dst\n");
    scanf("%d %d",&src,&dst);
    printf("input 1 for naive method, 2 for better method\n");
    scanf("%d",&method);
    printf("正在为您规划路径，请稍等\n");
    if(method==1)
        naiveshortestPath(G,src,dst);
    else
        bettershortestPath(G,src,dst);
    printf("input 1 to continue,0 to finish\n");
    scanf("%d",&flag);
}

return 0;

}
