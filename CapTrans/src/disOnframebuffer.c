#include "includes.h"

int fd_fb0;
long int screensize = 0;
char *fb_buf = 0;
struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;

void InitDisOnFrameBuffer()
{
	// Open the file for reading and writing
	fd_fb0 = open(DISON_FB0, O_RDWR);
	if (!fd_fb0) {
	    printf("Error: cannot open framebuffer device.\n");
	    exit(1);
	}
	printf("The framebuffer device was opened successfully.\n");

	// Get fixed screen information
	if (ioctl(fd_fb0, FBIOGET_FSCREENINFO, &finfo)) {
	    printf("Error reading fixed information.\n");
	    exit(2);
	}

	// Get variable screen information
	if (ioctl(fd_fb0, FBIOGET_VSCREENINFO, &vinfo)) {
	    printf("Error reading variable information.\n");
	    exit(3);
	}
	printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel );

	// Figure out the size of the screen in bytes
	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
	printf("screensize=%d\n",screensize);

	// Map the device to memory
	fb_buf = (char *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED,
		           fd_fb0, 0);
	if ((int)fb_buf == -1) {
	    printf("Error: failed to map framebuffer device to memory.\n");
	    exit(4);
	}
	printf("The framebuffer device was mapped to memory successfully.\n");
}
void DisOnFrameBuffer(unsigned char *frame)
{
	//memcpy(fb_buf,frame,640* 480* 3 * sizeof(char));
	int x = 0, y = 0;
	long int location = 0;
	// Figure out where in memory to put the pixel
	for ( y = 0; y < 480; y++ )
		for ( x = 0; x < 640; x++ ) {
			location = (x+vinfo.xoffset) * (vinfo.bits_per_pixel/8) +
					   (y+vinfo.yoffset) * finfo.line_length;
			if ( vinfo.bits_per_pixel == 32 ) {
				//rgb32 bgra
				*(fb_buf + location ) 		= *frame;frame++; // Some blue
				*(fb_buf + location + 1)	= *frame;frame++; // A little green
				*(fb_buf + location + 2) 	= *frame;frame++; //A lot of red//frame[480*y+x+2];
				*(fb_buf + location + 3) = 0; // No transparency
			}
			else { //assume 16bpp
				int b = 10;
				int g = (x-100)/6; // A little green
				int r = 31-(y-100)/16; // A lot of red
				unsigned short int t = r<<11 | g << 5 | b;
				*((unsigned short int*)(fb_buf + location)) = t;
			}
		}
}
void CloseDisOnFrameBuffer()
{
	munmap(fb_buf, screensize);
	close(fd_fb0);
}
