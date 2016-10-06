#ifndef __UDPTRANS_H
#define __UDPTRANS_H

#define SERVER_PORT 8000
#define MAXLINE 1024
#define BLOCKSIZE 38400
#define SEVER_IP "219.216.88.150"

struct udptransbuf//包格式
{
	char buf[BLOCKSIZE];//存放数据的变量
	char flag;//标志
};
void initUDPTrans();
void sendUDPdata(void *datas,unsigned int size);
void recUDPdata(char *udpRecbuf);
void closeUDPtrans();

#endif
