/*
 * File: console.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: this file is half a console manager, half a vga driver
 */

#include <atomos/kernel.h>
#include <atomos/mm.h>
#include <atomos/mman.h>

#include <asm/pgtable.h>

#define CON_WIDTH 1024
#define CON_HEIGHT 768

static u32 vid_memory;
static u32 w, h;

void console_init(u32 physbase_)
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
  return;
  
  goto resume;
  /*
  if (vid_memory)
    {
      if (((u32 *)vid_memory)[0] == 0xDEADFACE &&
	  ((u32 *)vid_memory)[1] == 0xCAFEBABE)
	printk(KERN_INFO, "Found video memory\n");
    }
  else
    {
      printk(KERN_INFO, "Video not found: %x\n", physbase_);
      return;
    }
  */
 resume:
  for (u16 y = 0; y < h; y++)
    {
      for (u16 x = 0; x < w; x++)
	{
	  ((u32 *)vid_memory)[x + y * w] = 0xffffffff;
	}
    }
}
