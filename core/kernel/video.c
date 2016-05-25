/*
 * File: video.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: little svga driver
 */

#include <kernel/pyr0.h>
#include <kernel/mm.h>
#include <kernel/mman.h>
#include <kernel/video.h>

#include <asm/pgtable.h>

#include <ui/terminal-font.h>

#include <string.h>

/* video module */

#define CHAR_WIDTH   8
#define CHAR_HEIGHT 12

#define FG_COLOR 0xff000000
#define BG_COLOR 0xffffffff

static u32 vid_memory;
static u32 w, h;

static void video_set_point(int x, int y, u32 value)
{
	u32 *disp = (u32*) vid_memory;
	u32 *cell = &disp[y * CON_WIDTH + x];

	*cell = value;
}

static void _video_putchar(int x, int y, unsigned char val, u32 color)
{
	u8 *c = number_font[val];

	for (u8 i = 0; i < CHAR_HEIGHT; ++i)
	{
		for(u8 j = 0; j < CHAR_WIDTH; ++j)
		{
			if(c[i] & (1 << (8-j)))
				video_set_point(x+j, y+i,color);
			else if(val == 0)
				video_set_point(x+j, y+i, BG_COLOR);
		}
	}
}

void video_putchar(int x, int y, char val)
{
	if (val == ' ') val = 0;
	_video_putchar(x*CHAR_WIDTH,y*CHAR_HEIGHT, val, FG_COLOR);
}

static void video_puts(int x, int y, char *val)
{
	for (val; *val!= '\0'; val++)
	{
		video_putchar(x, y, *val);
		x += 1;
	}
}

void video_scroll(unsigned n)
{
	/* XXX: works only for 1, for the moment */
	unsigned line_len = 4 * CON_WIDTH * CHAR_HEIGHT;

	for (unsigned i = 1; i < (CHAR_PER_COLUMN); i++)
	{
		memcpy((void*)(vid_memory + line_len * (i-1)),
		       (void *)(vid_memory + line_len * i),
		       line_len);

		if (i == (CHAR_PER_COLUMN -1))
			memset((void*)(vid_memory + line_len * i), 0xff, line_len);

	}
}


int video_init(u32 physbase_)
{
	w = CON_WIDTH;
	h = CON_HEIGHT;
	vid_memory = physbase_;

	/* test if there is memory */
	u32 *mem_test = (u32 *)0xa0000;
	mem_test[0] = 0xDEADFACE;
	mem_test[1] = 0xCAFEBABE;

	for (int i = 2; i < 1000; i+= 2)
	{
		mem_test[i] = 0xff00ff00;
		mem_test[i+1] = 0x00ff00ff;
	}

	for (u32 fb_offset = 0xe0000000; fb_offset < 0xff000000; fb_offset += 0x01000000)
	{
		for (u32 i = fb_offset; i <= fb_offset + 0xff0000; i+= 0x1000)
		{
			paging_map(i,i,P_KERNEL);
		}

		for (u32 x = fb_offset; x < fb_offset + 0xff0000; x += 0x1000)
		{
			if(((u32 *)x)[0] == 0xDEADFACE && ((u32 *)x)[1] == 0xCAFEBABE)
			{
				vid_memory = x;
				goto resume;
			}
		}
	}

	printk(KERN_INFO, "Video not found\n");
	return -1;

	goto resume;

resume:
	for (u16 y = 0; y < h; y++)
	{
		for (u16 x = 0; x < w; x++)
		{
			((u32 *)vid_memory)[x + y * w] = 0xffffffff;
		}
	}
	return 0;
}
