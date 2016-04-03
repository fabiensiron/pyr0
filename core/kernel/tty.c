/**
 * File: tty.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <atomos/kernel.h>
#include <atomos/serial.h>
#include <atomos/tty.h>

#include <string.h>
 
int tty_is_init = 0;
void rs_write(struct tty*);

struct tty tty_table[] = {
   {
     /* COM1 */
     rs_write,
     {1, 0, 0, ""},
     {1, 0, 0, ""}
   },
   {
     /* COM2 */
     rs_write,
     {2, 0, 0, ""},
     {2, 0, 0, ""}
   },
   {
     /* COM3 */
     rs_write,
     {3, 0, 0, ""},
     {3, 0, 0, ""}
   },
   {
     /* COM4 */
     rs_write,
     {4, 0, 0, ""},
     {4, 0, 0, ""}
   }
 };

struct tty_queue *table_list[] =
  {
    &tty_table[0].read_queue, &tty_table[0].write_queue,
    &tty_table[1].read_queue, &tty_table[1].write_queue
  };

#define PUTCH(c,writeq)				\
  do {						\
    writeq.buf[writeq.len] = c;			\
    writeq.len++;				\
  } while(0)					\

#define POPCH(readq)						\
  ({								\
    unsigned char _v;						\
    _v = readq.buf[readq.head];					\
    readq.len = readq.len -1;					\
    readq.head = (readq.len == 0)				\
      ? 0							\
      : (readq.head+1) % TTY_BUF_SIZE;				\
    _v;								\
  })

int tty_write(int c, const char *buf, size_t n)
{
  struct tty *tty;
  size_t i;
  
  if (c > 3)
    return -1;
  if (n > TTY_BUF_SIZE)
    return -1;
  
  tty = tty_table + c;
  tty->write_queue.len = 0;
  
  for (i = 0; i < n; i++)
    PUTCH(buf[i], tty->write_queue);

  tty->write(tty);

  return tty->write_queue.len;
}

# if 0
int tty_read(int c, char *buf, size_t n)
{
  struct tty *tty;
  size_t i;

  if (c > 3)
    return -1;
  if (n > TTY_BUF_SIZE)
    return -1;

  tty = tty_table + c;

}

# endif

unsigned char tty_getc()
{
  struct tty *tty;
  size_t i;

  tty = tty_table + 0; /* add channel */

  while(tty->read_queue.len == 0)
    ;

  return POPCH(tty->read_queue);
}

void rs_write(struct tty *tty)
{
  if (tty->write_queue.len)
    serial_write(tty->write_queue.data,
		 tty->write_queue.buf,
		 tty->write_queue.len);
}

void tty_init()
{
  tty_is_init = 1;
  serial_init();
}
