#include "includes.h"

int main()
{
	testCapVideo();
	//sleep(1);
	while(1)
	{
		//printf("sleep then disp\n");
		//sleep(5);
		dispVideo();
	}
	closeUDPtrans();
	CloseDisOnFrameBuffer();//πÿœ‘ æ
	stopCapture();
	freeBuffers();
	closeIPU();
	closeVideo();
	return 0;
}
