#include<unistd.h>
#include<stdio.h>
#include<sys/syscall.h>
#include<malloc.h>
int main(void){
	int result;
	int i=0;
	int pid3[500];
	int time3[500];
	syscall(332,&result,pid3,time3);
	printf("process number is %d\n",result);
	printf("PID\tTIME\n");
	for(i=0;i<result;i++){
		printf("%d\t%d\n",pid3[i],time3[i]);	
	}
	return 0;
}
