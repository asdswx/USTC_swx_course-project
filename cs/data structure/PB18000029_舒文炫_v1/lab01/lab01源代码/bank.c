#include"initial.h"
#include<stdlib.h>
#include"cusop.h"


int main(){
    int i,j,k;
    int flag=1;
    int re=1;
    float average;
    while(flag){
        if(re)
            initializebank();
        openforday();
        amountnow=total;

        while(pev->event_type!=0){
                    if(details){
                        printf("------\n");
                        print_event(pev);
                        print_queue(pw,windownum);
                        printf("��ʱ��:%d ���ڵĽ�Ǯ:%d �˿�����:%d\n",totaltime,amountnow,customernum);
                        printf("------\n");
                    }
                ev=deevent(pev);
                if(ev->event_type==0){
                    cus_arrived();
                }
                else{
                    cus_departure();

                }
                free(ev);


        }
        closethebank();
                    if(details){
                        printf("------\n");
                        print_event(pev);
                        print_queue(pw,windownum);
                        printf("��ʱ��:%d ���ڵĽ�Ǯ:%d �˿�����:%d\n",totaltime,amountnow,customernum);
                        printf("------\n");
                    }
        average=(float)totaltime/customernum;
        printf("ƽ������ʱ��Ϊ%f\n",average);
    printf("����ģ��������1����������0\n");
    scanf("%d",&flag);
    if(flag==0)
        break;
    printf("����ʹ�øղŵ���������0��������������1\n");
    scanf("%d",&re);
    if(re)
        reset();
    }

    return 0;
}
