#include "includes.h"


struct sockaddr_in serveraddr;
int confd;

char udpRecbuf[MAXLINE];

void initUDPTrans()
{
	//1.创建一个socket
	confd=socket(AF_INET,SOCK_DGRAM,0);
	//2.初始化服务器地址
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family=AF_INET;
	//
	inet_pton(AF_INET,SEVER_IP,&serveraddr.sin_addr.s_addr);
	serveraddr.sin_port =htons(SERVER_PORT);
}
void sendUDPdata(void *datas,unsigned int size)
{
	size_t len,i,j;//分成1800块 每块512
	char tempflag;
	struct udptransbuf data;
	for(i=0;i<24;i++){
		memcpy(data.buf,datas+i*BLOCKSIZE,BLOCKSIZE);
//		for(j=0;j<BLOCKSIZE;j++)
//			data.buf[j]= (unsigned char*)(datas+i*BLOCKSIZE+j);
		if(i==0){
			tempflag='a';
			data.flag=tempflag;
		}
		else{
			tempflag++;
			data.flag=tempflag;
		}
		//3向务器发送数据
		len=sendto(confd,(void*)&data,sizeof(data),0,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
		if(len<0)
			printf("UDP send failed\n");
	}
	//char udpSendbuf[MAXLINE]="125wwew3332354#@$#";
}
void recUDPdata(char *udpRecbuf)//这里要求传入的是数组，要是指针需要修改
{
	size_t len;
	len=recvfrom(confd,udpRecbuf,sizeof(udpRecbuf),0,NULL,0);
	write(STDIN_FILENO,udpRecbuf,len);
}
void closeUDPtrans()
{
	close(confd);
}
