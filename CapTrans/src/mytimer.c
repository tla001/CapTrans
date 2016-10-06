#include "includes.h"

unsigned char timer_alarm=0;
pthread_t tid_timer1,tid_timer2,tid_timer3;
int timer1_openflag,timer2_openflag,timer3_openflag;
pthread_rwlock_t rwlock;

void StartTimer1()
{
	int ret;
	//初始化读写所
	ret=pthread_rwlock_init(&rwlock, NULL);
	if(ret<0){
		printf("init wrlock failed\n");
	}
	timer1_openflag=1;
	pthread_create(&tid_timer1,NULL,&timer1_ms,NULL);
}
void CloseTimer1()
{
	timer1_openflag=0;
	//pthread_join(&tid_timer1,NULL);
}
void setTimer1(int seconds, int useconds)
{
        struct timeval temp;
        temp.tv_sec = seconds;
        temp.tv_usec = useconds;
        select(0, NULL, NULL, NULL, &temp);
       // printf("timer\n");
        return ;
}
void timer1_ms(void *vptr)
{
	//printf("timer start!\n");
	while(1){
		if(timer1_openflag==0)
			return;
		//setTimer1(0, 10);//100ms
		//后续处理
		timer_alarm=1;
		usleep(1);
		//printf("timer_alarm=%d\n",timer_alarm);
		pthread_rwlock_wrlock(&rwlock);
		getFrame((void **)&yuvFrame,&len);
		pthread_rwlock_unlock(&rwlock);
	}
}

void StartTimer2()
{
	timer2_openflag=1;
	pthread_create(&tid_timer2,NULL,&timer2_ms,NULL);
}
void CloseTimer2()
{
	timer2_openflag=0;
	//pthread_join(&tid_timer2,NULL);
}
void setTimer2(int seconds, int useconds)
{
        struct timeval temp;
        temp.tv_sec = seconds;
        temp.tv_usec = useconds;
        select(0, NULL, NULL, NULL, &temp);
       // printf("timer\n");
        return ;
}
void timer2_ms(void *vptr)
{
	//printf("timer start!\n");
	while(1){
		if(timer2_openflag==0)
			//goto timerout2;
			return;
		//setTimer2(0, 10);
		//后续处理
		//printf("timer2\n");
		usleep(1);
		pthread_rwlock_wrlock(&rwlock);
		convert_yuv_to_rgb_buffer(yuvFrame,rgbFrame,640,480);
		backFrame();
		pthread_rwlock_unlock(&rwlock);
		//将buffer返回队列
		//backFrame();
	}
	//timerout2:return;
}

void StartTimer3()
{
	timer3_openflag=1;
	pthread_create(&tid_timer3,NULL,&timer3_ms,NULL);
}
void CloseTimer3()
{
	timer3_openflag=0;
	//pthread_join(&tid_timer3,NULL);
}
void setTimer3(int seconds, int useconds)
{
        struct timeval temp;
        temp.tv_sec = seconds;
        temp.tv_usec = useconds;
        select(0, NULL, NULL, NULL, &temp);
       // printf("timer\n");
        return ;
}
void timer3_ms(void *vptr)
{
	//printf("timer start!\n");
	while(1){
		if(timer3_openflag==0)
			//goto timerout3;
			return;
		//setTimer3(0, 10);
		//后续处理
		//printf("timer3\n");
		usleep(1);
		pthread_rwlock_rdlock(&rwlock);
		DisOnFrameBuffer(rgbFrame);
		pthread_rwlock_unlock(&rwlock);
	}
	//timerout3:return;
}
