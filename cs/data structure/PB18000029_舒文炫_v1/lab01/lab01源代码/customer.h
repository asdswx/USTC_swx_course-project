#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

typedef struct event{//�¼���
    int occur_time;
    int event_type;
    int flag;
    struct event *next;

}Event,*pEvent;

typedef struct cus_queue{//�ڸ������ڵĶ���
    int arrive_time;
    int duartion;
    int amount;
    int flag;
    struct cus_queue *next;
}cus_queue;


typedef struct windows{//ÿ������
    int queuelen;
    struct cus_queue *head,*tail;

}windows,*pwindows;

pEvent pev,ev;

pwindows pw;
#endif
