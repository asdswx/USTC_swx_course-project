#include"customer.h"
#include<malloc.h>
#ifndef _EVENT_H_
#define _EVENT_H_


pEvent init_event();//初始化事件表
int print_event(pEvent p);//打印事件表
int orderinsert(pEvent p,pEvent a);//按序插入事件
pEvent makeevent(int a,int b);//创建事件
pEvent deevent(pEvent p);//删除事件
int reconductevent(pEvent p,int a);//重建事件表
int resetflag(pEvent p);//重设事件的flag

pEvent init_event(){
    pEvent q;
    q=(pEvent)malloc(sizeof(Event));
    q->event_type=0;
    q->occur_time=-1;
    q->flag=0;
    q->next=NULL;
    return q;


}

pEvent makeevent(int a,int b){
    pEvent p;
    p=(pEvent)malloc(sizeof(Event));
    p->event_type=b;
    p->occur_time=a;
    p->flag=0;
    p->next=NULL;

    return p;

}



int print_event(pEvent p){
    pEvent q;
    q=p;
    while(q!=NULL){
        printf("%d %d->",q->event_type,q->occur_time);
        q=q->next;
    }
    printf("\n");
    return 0;
}


int orderinsert(pEvent p,pEvent a){
    pEvent q,r;
    q=p;

    while(q->next!=NULL){
        if(q->next->occur_time<a->occur_time){
            q=q->next;
        }
        else{
            a->next=q->next;
            q->next=a;
            p->event_type++;
            break;
        }
    }
    if(q->next==NULL){
            a->next=q->next;
            q->next=a;
            p->event_type++;
    }
    return 0;
}

pEvent deevent(pEvent p){
    pEvent q;
    q=p;
    if(p->next!=NULL){
        q=p->next;
        p->next=p->next->next;
        p->event_type--;

    }
    return q;



}

int resetflag(pEvent p){

    pEvent q;
    q=p;
    while(q->next!=NULL){
        q->next->flag=0;
        q=q->next;
    }
    return 0;

}

int reconductevent(pEvent p,int a){
    pEvent q,s;

    q=p;
    while(q->next!=NULL){
        if(q->next->event_type!=0&&q->next->flag!=1){
            p->event_type--;
            s=q->next;

            q->next=q->next->next;
            s->next=NULL;
            s->occur_time=s->occur_time+a;
            s->flag=1;
            orderinsert(p,s);
        }
        else
            q=q->next;
    }
    resetflag(p);
}

#endif // _EVENT_H_
