/*
 * File: kbd.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

#include <kernel/kernel.h>
#include <kernel/interrupt.h>
#include <kernel/console.h>
#include <kernel/tty.h>

#include <asm/io.h>

#define SHIFT_MODIFIER 0x2a
#define SHIFT_MODIFIER_RELEASED 0xaa

s32 last_key = -1;
extern unsigned char console_is_init;
extern struct tty_queue *table_list[];

u8 us_keymap[] = 
  {
    0, 0,  // 0x0
    '1','2','3','4','5','6','7','8','9','0', // 0x1
    '-','=', '\b', '\t',  // 0x0c
    'q','w','e','r','t','y','u','i','o','p', // 0x10
    '[',']', '\n', 0, // 0x1A
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

u8 us_keymap_cap[] =
  {
    0, 0,  // 0x0
    '!','@','#','$','%','^','&','*','(',')', // 0x1
    '_','+', '\b', '\t',  // 0x0c
    'Q','W','E','R','T','Y','U','I','O','P', // 0x10
    '{','}', '\n', 0, // 0x1A
    'A','S','D','F','G','H','J','K','L', // 0x1e
    ':','"','~', 0,'|', //0x27
    'Z','X','C','V','B','N','M', // 0x2c
    '<','>','?', 0,'*', 0,' ', 0, //0x33
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    '7','8','9','-','4','5','6','+', // 0x47
    '1','2','3','0','.', // 0x4f
    0,0,0,0,
    0,0
  };

u8 dv_keymap[] = 
  {
    0, 0,  // 0x0
    '1','2','3','4','5','6','7','8','9','0', // 0x1
    '[',']', '\b', '\t',  // 0x0c
    '\'',',','.','p','y','f','g','c','r','l', // 0x10
    '/','=', '\n', 0, // 0x1A
    'a','o','e','u','i','d','h','t','n', // 0x1e
    's','-','`', 0,'\\', //0x27
    ';','q','j','k','x','b','m', // 0x2c
    'w','v','z', 0,'*', 0,' ', 0, //0x33
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    '7','8','9','-','4','5','6','+', // 0x47
    '1','2','3','0','.', // 0x4f
    0,0,0,0,
    0,0
  };

u8 dv_keymap_cap[] =
  {
    0, 0,  // 0x0
    '!','@','#','$','%','^','&','*','(',')', // 0x1
    '{','}', '\b', '\t',  // 0x0c
    '"','<','>','P','Y','F','G','C','R','L', // 0x10
    '?','+', '\n', 0, // 0x1A
    'A','O','E','U','I','D','H','T','N', // 0x1e
    'S','_','~', 0,'|', //0x27
    ':','Q','J','K','X','B','M', // 0x2c
    'W','V','Z', 0,'*', 0,' ', 0, //0x33
    0,0,0,0,
    0,0,0,0,
    0,0,0,0,
    '7','8','9','-','4','5','6','+', // 0x47
    '1','2','3','0','.', // 0x4f
    0,0,0,0,
    0,0
  };

static u8 *keymap = us_keymap;
static u8 *keymap_cap = us_keymap_cap;

void kbd_set_keymap(u8 keymap_ /* 0 for us, 1 for dv */)
{
  switch (keymap_)
    {
    case 0:
      {
	keymap = us_keymap;
	keymap_cap = us_keymap_cap;
	break;
      }
    case 1:
      {
	keymap = dv_keymap;
	keymap_cap = dv_keymap_cap;
	break;
      }
    }
}

void kbd_wrapper (void);

void kbd_routine (void)
{
  static u8  shift_modifier = 0;
  u8 c = inb(0x60);

  switch (c)
    {
    case (SHIFT_MODIFIER_RELEASED):
      shift_modifier = 0;
      return;
    case (SHIFT_MODIFIER):
      shift_modifier = 1;
      return;
    }
  
  if (!(c & 0x80))
    last_key = c & 0x7f;

  if (console_is_init & !(c & 0x80))
    {
      if (shift_modifier)
	table_list[0]->
	  buf[(table_list[0]->len + table_list[0]->head) % TTY_BUF_SIZE] =
	  keymap_cap[last_key];
      else
	table_list[0]->
	  buf[(table_list[0]->len + table_list[0]->head) % TTY_BUF_SIZE] =
	  keymap[last_key];

      table_list[0]->len = ((table_list[0]->len + 1) > TTY_BUF_SIZE)
	? table_list[0]->len
	: table_list[0]->len + 1;

      if (shift_modifier)
	console_putchar(keymap_cap[last_key]);
      else
	console_putchar(keymap[last_key]);
    }
}

void kbd_init (void)
{
  setup_irq(1, kbd_routine);
}

int getkey (void)
{
  return last_key;
}
