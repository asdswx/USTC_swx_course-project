#include<stdio.h>
#include<malloc.h>
#include"settings.h"
#include"eventop.h"
#include"queueop.h"
#include"customer.h"
#include<stdlib.h>
#include<time.h>


int initializebank();//初始化银行，主要是给出模拟交互界面
int openforday();//银行开门营业


int initializebank(){//对银行进行初始化设定
    int i;
    printf("欢迎进入银行业务模拟系统，输入0跳过初始化，使用系统默认设定，输入1进入设定\n");
    scanf("%d",&i);
    printf("是否查看详情,是输入1，否输入0\n");
    scanf("%d",&details);
    if(i==0){
        printf("进入银行\n");
    }
    else{
        printf("输入银行总额以及营业时间\n");
        scanf("%d %d",&total,&closetime);
        printf("输入第一种窗口个数\n");
        scanf("%d",&windownum);
        printf("输入顾客到达时间间隔范围和最短时间间隔\n");
        scanf("%d %d",&arrive_interval,&arrive_min);
        printf("输入顾客交易时间间隔范围和最短时间间隔\n");
        scanf("%d %d",&transaction_interval,&transaction_min);
        printf("输入顾客交易的金额范围以及最小交易金额数\n");
        scanf("%d %d",&transaction_amount,&transaction_minamount);

        printf("初始化完成,进入银行\n");

    }
    return 0;
}

int openforday(){
    int i;
    totaltime=0;
    customernum=0;
    distime=0;
    lastdisoccur=0;
    pev=init_event();
    ev=makeevent(0,0);
    orderinsert(pev,ev);
    srand((unsigned)time(NULL));
    pw=(pwindows)malloc((windownum+1)*sizeof(windows));
    for(i=0;i<windownum+1;i++){
        pw[i].queuelen=0;
        pw[i].head=init_queue();
        pw[i].tail=pw[i].head;


    }


}
