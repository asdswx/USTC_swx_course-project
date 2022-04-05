#include"customer.h"
#include<malloc.h>
#ifndef _QUEUEOP_H_
#define _QUEUEOP_H_

cus_queue* init_queue();//初始化客户队列
int print_queue(pwindows p,int a);//打印队列
int minqueue(pwindows p);//求最短队列
int enqueue(pwindows p,int i,int a,int b,int c);//客户入队列
cus_queue* makecus(int a,int b,int c);//创建客户
cus_queue* dequeue(pwindows p,int i);//删除对应窗口的客户
cus_queue* gethead(pwindows p,int i);//得到对应窗口队列的头
int checkqueue(pwindows p,int a);//检查第二种队列

cus_queue* init_queue(){
    cus_queue* q;
    q=(cus_queue*)malloc(sizeof(cus_queue));
    q->amount=0;
    q->arrive_time=-1;
    q->duartion=-1;
    q->flag=0;
    q->next=NULL;
    return q;

}
int print_queue(pwindows p,int a){
    int i;
    cus_queue* q;
    for(i=0;i<a+1;i++){
        q=p[i].head;
        printf("%d\n",p[i].queuelen);
        while(q!=NULL){
            printf("%d %d %d->",q->amount,q->arrive_time,q->duartion);
            q=q->next;
        }
        printf("\n");

    }
    return 0;

}

int minqueue(pwindows p){
    int i,j;
    j=0;
    for(i=0;i<windownum;i++){
        if(p[i].queuelen<p[j].queuelen){
            j=i;
            break;
        }
    }
    return j;
}

cus_queue* makecus(int a,int b,int c){
    cus_queue* p;
    p=(cus_queue*)malloc(sizeof(cus_queue));
    p->arrive_time=a;
    p->duartion=b;
    p->amount=c;
    p->flag=0;
    p->next=NULL;

    return p;


}

int enqueue(pwindows p,int i,int a,int b,int c){
    cus_queue* q;
    q=makecus(a,b,c);
    p[i].tail->next=q;
    p[i].tail=q;
    p[i].queuelen++;
    return 0;
}

cus_queue* dequeue(pwindows p,int i){
    cus_queue* q;
    q=p[i].head->next;
    p[i].head->next=p[i].head->next->next;
    if(p[i].head->next==NULL){
        p[i].tail=p[i].head;
    }
    q->next=NULL;
    p[i].queuelen--;

    return q;

}

cus_queue* gethead(pwindows p,int i){

    return(p[i].head->next);


}

int checkqueue(pwindows p,int a){//a为银行收到资金前的剩余资金
    cus_queue* q,*qaq;
    cus_queue* r;
    distime=0;
    if(p[windownum].head->next!=NULL){//windownum对应的队列就是第二种队列，此时中断第一种队列的服务
        do{
            if(amountnow>=-p[windownum].head->next->amount){//当目前资金还可以满足第二种队列的客户时
                r=dequeue(pw,windownum);
                distime=distime+r->duartion;//distime是处理第二种队列里面客户导致的延迟时间
                amountnow=amountnow+r->amount;
                totaltime=totaltime+ev->occur_time+distime-r->arrive_time;//处理完该用户，总等待时间增加
                free(r);

            }
            else{//当前资金无法满足当前客户，循环查看后面的客户
                if(p[windownum].queuelen>1){
                        printf("%d ",p[windownum].head->next->amount);

                    qaq=p[windownum].head->next;
                    qaq->flag=1;//访问过的客户flag置1 ，防止重复访问，同时将该客户插入到队尾
                    p[windownum].head->next=p[windownum].head->next->next;
                    qaq->next=p[windownum].tail->next;
                    p[windownum].tail->next=qaq;
                    p[windownum].tail=p[windownum].tail->next;
                }
                else{
                qaq=p[windownum].head->next;
                    qaq->flag=1;
                }
            }//队列全部访问了一遍或者银行当前资金少于a就停止循环，此时无法满足后面的客户了
        }while(p[windownum].head->next!=NULL&&p[windownum].head->next->flag!=1&&amountnow>a);


    if(p[windownum].head->next!=NULL){//重设flag
        q=p[windownum].head->next;
        while(q!=NULL){
            q->flag=0;
            q=q->next;
        }
    }
    lastdisoccur=ev->occur_time;//上一次中断发生时间
    }


    return 0;
}



#endif // _QUEUEOP_H_
