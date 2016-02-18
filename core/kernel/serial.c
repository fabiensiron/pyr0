/**
 * File: serial.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: serial device driver
 */

#include <atomos/kernel.h>

#include <asm/io.h>

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

#define LSR  5

static inline
u16 idx2com(int idx)
{
  switch(idx)
    {
    case 1:
      return COM1;
    case 2:
      return COM2;
    case 3:
      return COM3;
    case 4:
      return COM4;
    default:
      return COM1;
    }
}


static
void init (u16 port, u16 rate)
{
  u16 div = 115200 / rate;
  
  outb(port+1, 0);
  outb(port+3, 0x80);
  outb(port, div & 0xff);
  outb(port+1, div >> 8);
  outb(port+3, 0x03);
  outb(port+2, 0xc7);
  outb(port+4, 0xb);
}

void serial_early_init()
{
  init(COM1, 38400);
}

void serial_init()
{
  /* serial_early_init must be called first */
  init(COM2, 38400);
  init(COM3, 38400);
  init(COM4, 38400);
}

static
void serial_putchar(u16 port, char c)
{
  while(!((inb(port+LSR)) & 0x20))
    ;

  outb(port, c);
}

size_t serial_write(int index, const char *buf, size_t len)
{
  unsigned i;

  for (i = 0; i < len; i++)
    serial_putchar(idx2com(index), buf[i]);

  return i;
}
