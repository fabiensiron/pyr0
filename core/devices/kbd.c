/*
 * File: kbd.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

#include <atomos/kernel.h>
#include <atomos/interrupt.h>
#include <atomos/console.h>

#include <asm/io.h>

s32 last_key = -1;
extern unsigned char console_is_init;

u8 keymap[] = 
  {
    0, 0,  // 0x0
    '1','2','3','4','5','6','7','8','9','0', // 0x1
    '-','=', 0, 0,  // 0x0c
    'q','w','e','r','t','y','u','i','o','p', // 0x10
    '[',']', 0, 0, // 0x1A
    'a','s','d','f','g','h','j','k','l', // 0x1e
    ';','\'','`', 0,'\\', //0x27
    'z','x','c','v','b','n','m', // 0x2c
    ',','.','/', 0,'*', 0,' ', 0, //0x33
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    '7','8','9','-','4','5','6','+', // 0x47
    '1','2','3','0','.', // 0x4f
    0,0,0,0,
    0,0
  };

void kbd_wrapper (void);

void kbd_routine (void)
{
  u8 c = inb(0x60);
  if (!(c & 0x80))
    last_key = c & 0x7f;

  if (console_is_init & !(c & 0x80))
    console_putchar(keymap[last_key]);
}

void kbd_init (void)
{
  setup_irq(1, kbd_routine);
}

int getkey (void)
{
  return last_key;
}
