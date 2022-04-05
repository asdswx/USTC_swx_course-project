#include"eventop.h"
#include"queueop.h"
#include"settings.h"
#include<stdlib.h>
#include<time.h>

int cus_arrived();//����ͻ������¼�
int cus_departure();//����ͻ��뿪�¼�
int closethebank();//���й��ţ�������Ҫ������ʣ���û����Ŀͻ�������������Ҳ��Կͻ�����

int cus_arrived(){
    int inter_time;
    int dur_time;
    int cus_amount;
    int t,i;
    pEvent a,b;
    customernum++;
    //��ǰ�ͻ�����ʱ��������������õ���һ���ͻ�����ʱ�䣬���׽��
    dur_time=rand()%transaction_interval+transaction_min;
    inter_time=rand()%arrive_interval+arrive_min;
    cus_amount=rand()%transaction_amount+transaction_minamount;
    t=ev->occur_time+inter_time;


    if(t<closetime){//��һ���ͻ������й���ǰ�����ͽ���һ���ͻ��ĵ����¼������¼���
        a=makeevent(t,0);
        orderinsert(pev,a);
    }
        i=minqueue(pw);//����ǰ�ͻ����뵽�ӳ���̵Ķ��еĴ���
        enqueue(pw,i,ev->occur_time,dur_time,cus_amount);

    if(pw[i].queuelen==1){//�����ǰ���еĳ���Ϊ1����ô�Ϳ��Բ����ÿͻ����뿪�¼���
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
    if(ev->occur_time<=closetime){//�뿪�¼������й���֮ǰ
        if(cusqwq->amount<=0){//�ͻ���Ҫȡ��
            if(amountnow+cusqwq->amount<0)//����û���㹻�ʽ����㣬���ͻ����뵽�ڶ��ֶ���
                enqueue(pw,windownum,cusqwq->arrive_time,cusqwq->duartion,cusqwq->amount);
            else{//���п������㣬����ÿͻ�
                amountnow=amountnow+cusqwq->amount;
                totaltime=totaltime+ev->occur_time-cusqwq->arrive_time;
            }
        }
        else{//�ͻ���Ҫ���
            j=amountnow;//j�ȱ��浱ǰ�����ʽ�
            amountnow=amountnow+cusqwq->amount;
            totaltime=totaltime+ev->occur_time-cusqwq->arrive_time;
            checkqueue(pw,j);//���п�ʼ����ڶ��ֶ��еĿͻ���ֱ���ʽ�С��j����ʱ��õ��жϳ���ʱ����жϿ�ʼʱ��
            printf("@@@@@%d %d\n",distime,lastdisoccur);
            if(distime!=0)//�������жϣ��ؽ��¼���,��Ҫ�Ƕ��Ѿ����ڵ��뿪�¼������Ƴ�
                disflag=1;
                reconductevent(pev,distime);
        }
            free(cusqwq);
            if(pw[i-1].queuelen!=0){//������ǰ������һ���ͻ����뿪�¼�
                cusqwq=gethead(pw,i-1);
                if(disflag==1){//�������жϣ���һ���ͻ����뿪ʱ��ᱻ�Ƴ�
                    qwq=makeevent(lastdisoccur+distime+cusqwq->duartion,i);
                }
                else //û�жϣ���һ���ͻ����������뿪
                    qwq=makeevent(ev->occur_time+cusqwq->duartion,i);
                orderinsert(pev,qwq);
            }

    }
    else{//�뿪�¼������й��ź󣬲����κδ���ֱ�Ӱѵȴ�ʱ�����
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



