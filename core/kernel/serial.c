/**
 * File: serial.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: serial device driver
 */
#include <string.h>

#include <kernel/kernel.h>
#include <kernel/interrupt.h>
#include <kernel/tty.h>

#include <asm/io.h>

extern struct tty_queue *table_list[];

#define COM1 0x3f8
#define COM2 0x2f8
#define COM3 0x3e8
#define COM4 0x2e8

#define LSR  5
#define IIR  2

#define BUFFER_SERIAL_LEN 160

struct serial_internal
{
  u8 buffer[BUFFER_SERIAL_LEN];  
  unsigned int buffer_len;
  unsigned int position;
};

struct serial_internal serial_internal_a;
//struct serial_internal serial_internal_b;

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
void serial_putchar(u16 port, char c)
{
  while(!((inb(port+LSR)) & 0x20))
    ;

  outb(port, c);
}

static
char serial_getchar(u16 port)
{
  char lsr = inb(port + LSR);

  if (!(lsr & 0x01))
    return -1;

  char c = inb(port);

  if (c == 0xd)
    {
      //      serial_putchar(COM1, '\n');
      return '\n';
    }

  return c;
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

  outb(port+1,0x01);
}

static
void serial_handler(void)
{
  char c;
  
  if (inb(COM1 + IIR) & 0x01)
    return;

  while((c = serial_getchar(COM1)) != -1)
   { 
     //     serial_internal_a.buffer[serial_internal_a.position++] = c;
     table_list[0]->
       buf[(table_list[0]->len + table_list[0]->head) % TTY_BUF_SIZE] = c;
     
     table_list[0]->len = ((table_list[0]->len + 1) > TTY_BUF_SIZE)
       ? table_list[0]->len
       : table_list[0]->len + 1;
     
     serial_putchar(COM1, c);
   }
}

size_t serial_write(int index, const char *buf, size_t len)
{
  unsigned i;

  for (i = 0; i < len; i++)
    serial_putchar(idx2com(index), buf[i]);

  return i;
}
#if 0
size_t serial_read(int index, char *buf, size_t len)
{
  size_t toread = len > serial_internal_a.position
    ? serial_internal_a.position 
    : len;

  /* this function works only for COM1 for the moment */
  int com = idx2com(index);
  assert(com == COM1);

  while (serial_internal_a.buffer[serial_internal_a.position] == 0xd)
    ;

  memcpy(buf, serial_internal_a.buffer, toread);
  memcpy(serial_internal_a.buffer,
	 serial_internal_a.buffer + toread,
	 serial_internal_a.position - toread);

  serial_internal_a.position -= toread;

  return toread;
}
#endif
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

  /* init COM1 input */
  memset(serial_internal_a.buffer, 0, BUFFER_SERIAL_LEN);

  serial_internal_a.buffer_len = BUFFER_SERIAL_LEN;
  serial_internal_a.position = 0;

  setup_irq(4, serial_handler);
  //  setup_irq(3, serial_handler);
}

