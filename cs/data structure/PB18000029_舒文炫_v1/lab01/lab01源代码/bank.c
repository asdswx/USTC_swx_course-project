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
                        printf("总时间:%d 现在的金钱:%d 顾客总数:%d\n",totaltime,amountnow,customernum);
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
                        printf("总时间:%d 现在的金钱:%d 顾客总数:%d\n",totaltime,amountnow,customernum);
                        printf("------\n");
                    }
        average=(float)totaltime/customernum;
        printf("平均逗留时间为%f\n",average);
    printf("继续模拟请输入1，否则输入0\n");
    scanf("%d",&flag);
    if(flag==0)
        break;
    printf("继续使用刚才的配置输入0，调整配置输入1\n");
    scanf("%d",&re);
    if(re)
        reset();
    }

    return 0;
}
