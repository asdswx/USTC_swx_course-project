#include"graphop.h"

int main(){
int start,compress_en;
ALGraph* G;
printf("if you have the bitfile already,please input 0,or input 1 to generate it\n");
scanf("%d",&start);
if(start){
preprocfile();
procbitfile();
}
printf("do you want to compress it?if so input 1 or input 0\n");
scanf("%d",&compress_en);
if(compress_en){
    G=Create_Graph();
    turnbitfile(G);
}
printf("you have got the bitfile,please close the window\n");
return 0;
}
