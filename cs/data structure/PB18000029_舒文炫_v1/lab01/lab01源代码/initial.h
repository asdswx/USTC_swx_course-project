#include<stdio.h>
#include<malloc.h>
#include"settings.h"
#include"eventop.h"
#include"queueop.h"
#include"customer.h"
#include<stdlib.h>
#include<time.h>


int initializebank();//��ʼ�����У���Ҫ�Ǹ���ģ�⽻������
int openforday();//���п���Ӫҵ


int initializebank(){//�����н��г�ʼ���趨
    int i;
    printf("��ӭ��������ҵ��ģ��ϵͳ������0������ʼ����ʹ��ϵͳĬ���趨������1�����趨\n");
    scanf("%d",&i);
    printf("�Ƿ�鿴����,������1��������0\n");
    scanf("%d",&details);
    if(i==0){
        printf("��������\n");
    }
    else{
        printf("���������ܶ��Լ�Ӫҵʱ��\n");
        scanf("%d %d",&total,&closetime);
        printf("�����һ�ִ��ڸ���\n");
        scanf("%d",&windownum);
        printf("����˿͵���ʱ������Χ�����ʱ����\n");
        scanf("%d %d",&arrive_interval,&arrive_min);
        printf("����˿ͽ���ʱ������Χ�����ʱ����\n");
        scanf("%d %d",&transaction_interval,&transaction_min);
        printf("����˿ͽ��׵Ľ�Χ�Լ���С���׽����\n");
        scanf("%d %d",&transaction_amount,&transaction_minamount);

        printf("��ʼ�����,��������\n");

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
