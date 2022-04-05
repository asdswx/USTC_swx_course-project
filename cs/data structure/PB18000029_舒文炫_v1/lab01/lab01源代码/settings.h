#ifndef _SETTINGS_H_
#define _SETTINGS_H_

int total=10000;
int closetime=600;
int windownum=2;
int arrive_interval=10;
int arrive_min=1;
int transaction_interval=6;
int transaction_min=5;
int transaction_amount=500;
int transaction_minamount=-350;
int details=0;
int totaltime;
int customernum;
int amountnow;
int distime=0;
int lastdisoccur=0;

int reset(){

    total=10000;
    closetime=600;
    windownum=2;
    arrive_interval=10;
    arrive_min=1;
    transaction_interval=6;
    transaction_min=5;
    transaction_amount=500;
    transaction_minamount=-350;
    details=0;
    distime=0;
    lastdisoccur=0;

}
#endif // _SETTINGS_H_
