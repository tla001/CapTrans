#include "includes.h"

unsigned char *rgbFrame=NULL;
unsigned char *yuvFrame=NULL;
unsigned int len;
/*************�������****************
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
	//ת������
	ret=getFrame((void **)&yuvFrame,&len);
	if(ret<0){
		printf("getFrame exit\n");
		exit(-1);
	}
	convert_yuv_to_rgb_buffer(yuvFrame,rgbFrame,640,480);
	//��ʾ����
	//printf("disp\n");
	DisOnFrameBuffer(rgbFrame);
	//��buffer���ض���
	ret=backFrame();
	if(ret<0){
			printf("backFrame exit\n");
			exit(-1);
	}
}
*/
/*************IPU����****************/
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
	//ת������
	ret=getFrame((void **)&yuvFrame,&len);
	if(ret<0){
		printf("getFrame exit\n");
		exit(-1);
	}
	printf("getFrame return len=%d\n",len);
	IPUConvent(yuvFrame,rgbFrame);
	//��ʾ����
	//printf("disp\n");
	DisOnFrameBuffer(rgbFrame);
	sendUDPdata(rgbFrame,ipuOutputSize);
	//��buffer���ض���
	ret=backFrame();
	if(ret<0){
			printf("backFrame exit\n");
			exit(-1);
	}
}
