#include"eventop.h"
#include"queueop.h"
#include"settings.h"
#include<stdlib.h>
#include<time.h>

int cus_arrived();//处理客户到来事件
int cus_departure();//处理客户离开事件
int closethebank();//银行关门，这里需要对银行剩余的没服务的客户进行清理，所以也算对客户操作

int cus_arrived(){
    int inter_time;
    int dur_time;
    int cus_amount;
    int t,i;
    pEvent a,b;
    customernum++;
    //当前客户到来时产生随机数用来得到下一个客户交易时间，交易金额
    dur_time=rand()%transaction_interval+transaction_min;
    inter_time=rand()%arrive_interval+arrive_min;
    cus_amount=rand()%transaction_amount+transaction_minamount;
    t=ev->occur_time+inter_time;


    if(t<closetime){//下一个客户在银行关门前到来就将下一个客户的到来事件加入事件表
        a=makeevent(t,0);
        orderinsert(pev,a);
    }
        i=minqueue(pw);//将当前客户插入到队长最短的队列的窗口
        enqueue(pw,i,ev->occur_time,dur_time,cus_amount);

    if(pw[i].queuelen==1){//如果当前队列的长度为1，那么就可以产生该客户的离开事件了
        if(lastdisoccur+distime<ev->occur_time){
            b=makeevent(ev->occur_time+dur_time,i+1);
            orderinsert(pev,b);
        }
        else{
            b=makeevent(distime+lastdisoccur+dur_time,i+1);
            orderinsert(pev,b);
        }


    }
    return 0;
}

int cus_departure(){
    int i,j;
    pEvent qwq;
    cus_queue* cusqwq;
    i=ev->event_type;
    cusqwq=dequeue(pw,i-1);
    int disflag;
    disflag=0;
    if(ev->occur_time<=closetime){//离开事件在银行关门之前
        if(cusqwq->amount<=0){//客户想要取款
            if(amountnow+cusqwq->amount<0)//银行没有足够资金满足，将客户插入到第二种队列
                enqueue(pw,windownum,cusqwq->arrive_time,cusqwq->duartion,cusqwq->amount);
            else{//银行可以满足，服务该客户
                amountnow=amountnow+cusqwq->amount;
                totaltime=totaltime+ev->occur_time-cusqwq->arrive_time;
            }
        }
        else{//客户想要存款
            j=amountnow;//j先保存当前银行资金
            amountnow=amountnow+cusqwq->amount;
            totaltime=totaltime+ev->occur_time-cusqwq->arrive_time;
            checkqueue(pw,j);//银行开始服务第二种队列的客户，直到资金小于j，这时会得到中断持续时间和中断开始时间
            printf("@@@@@%d %d\n",distime,lastdisoccur);
            if(distime!=0)//发生了中断，重建事件表,主要是对已经存在的离开事件进行推迟
                disflag=1;
                reconductevent(pev,distime);
        }
            free(cusqwq);
            if(pw[i-1].queuelen!=0){//产生当前窗口下一个客户的离开事件
                cusqwq=gethead(pw,i-1);
                if(disflag==1){//发生了中断，下一个客户的离开时间会被推迟
                    qwq=makeevent(lastdisoccur+distime+cusqwq->duartion,i);
                }
                else //没中断，下一个客户可以正常离开
                    qwq=makeevent(ev->occur_time+cusqwq->duartion,i);
                orderinsert(pev,qwq);
            }

    }
    else{//离开事件在银行关门后，不做任何处理，直接把等待时间加上
        totaltime=totaltime+closetime-cusqwq->arrive_time;
    }







}

int closethebank(){
    cus_queue* qwq;
    int i;
    for(i=0;i<windownum+1;i++){


    while(pw[i].head->next!=NULL){
        qwq=dequeue(pw,i);
        totaltime=totaltime+closetime-qwq->arrive_time;
        free(qwq);
    }
    }
    return 0;

}



