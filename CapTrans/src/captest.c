#include "includes.h"

unsigned char *rgbFrame=NULL;
unsigned char *yuvFrame=NULL;
unsigned int len;
/*************软件解码****************
void testCapVideo()
{
	rgbFrame=(unsigned char *)malloc(640* 480* 3 * sizeof(char));
	initVideo();
	InitDisOnFrameBuffer();
	if(startCapture()<0){
		printf("start capture failed\n");
		closeVideo();
		exit(-1);
	}
//	StartTimer1();
//	StartTimer2();
//	StartTimer3();
}

void dispVideo()
{
	int ret;
	//转换部分
	ret=getFrame((void **)&yuvFrame,&len);
	if(ret<0){
		printf("getFrame exit\n");
		exit(-1);
	}
	convert_yuv_to_rgb_buffer(yuvFrame,rgbFrame,640,480);
	//显示部分
	//printf("disp\n");
	DisOnFrameBuffer(rgbFrame);
	//将buffer返回队列
	ret=backFrame();
	if(ret<0){
			printf("backFrame exit\n");
			exit(-1);
	}
}
*/
/*************IPU解码****************/
void testCapVideo()
{
	rgbFrame=(unsigned char *)malloc(640* 480* 3 * sizeof(char));
	initVideo();
	InitDisOnFrameBuffer();
	initIPU();
	initUDPTrans();
	if(startCapture()<0){
		printf("start capture failed\n");
		closeVideo();
		exit(-1);
	}

}
void dispVideo()
{
	int ret;
	//转换部分
	ret=getFrame((void **)&yuvFrame,&len);
	if(ret<0){
		printf("getFrame exit\n");
		exit(-1);
	}
	printf("getFrame return len=%d\n",len);
	IPUConvent(yuvFrame,rgbFrame);
	//显示部分
	//printf("disp\n");
	DisOnFrameBuffer(rgbFrame);
	sendUDPdata(rgbFrame,ipuOutputSize);
	//将buffer返回队列
	ret=backFrame();
	if(ret<0){
			printf("backFrame exit\n");
			exit(-1);
	}
}
