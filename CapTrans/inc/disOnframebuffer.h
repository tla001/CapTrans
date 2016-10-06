#ifndef __DISONFRAMEBUFFER_H
#define __DISONFRAMEBUFFER_H

#define DISON_FB0	"/dev/fb0"

int fd_fb0;
extern long int screensize;
extern char *fb_buf;
extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;

void InitDisOnFrameBuffer();
void CloseDisOnFrameBuffer();
void DisOnFrameBuffer(unsigned char *frame);

#endif
