#ifndef __MYTIMER_H
#define __MYTIMER_H

#include <pthread.h>

extern unsigned char timer_alarm;
extern pthread_t tid_timer1,tid_timer2,tid_timer3;
extern int timer1_openflag,timer2_openflag,timer3_openflag;
extern pthread_rwlock_t rwlock;

void timer1_ms(void *vptr);
void setTimer1(int seconds, int useconds);
void StartTimer1();
void CloseTimer1();

void timer2_ms(void *vptr);
void setTimer2(int seconds, int useconds);
void StartTimer2();
void CloseTimer2();

void timer3_ms(void *vptr);
void setTimer3(int seconds, int useconds);
void StartTimer3();
void CloseTimer3();


#endif
