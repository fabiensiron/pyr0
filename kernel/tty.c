/**
 * File: tty.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <atomos/kernel.h>
#include <atomos/serial.h>
#include <atomos/tty.h>
 
 void rs_write(struct tty*);

 struct tty tty_table[] = {
   {
     /* COM1 */
     rs_write,
     {1, 0, ""}
   },
   {
     /* COM2 */
     rs_write,
     {2, 0, ""}
   },
   {
     /* COM3 */
     rs_write,
     {3, 0, ""}
   },
   {
     /* COM4 */
     rs_write,
     {4, 0, ""}
   }
 };

#define PUTCH(c,writeq)				\
  do {						\
    writeq.buf[writeq.len] = c;			\
    writeq.len++;				\
  } while(0)					\


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

void rs_write(struct tty *tty)
{
  if (tty->write_queue.len)
    serial_write(tty->write_queue.data,
		 tty->write_queue.buf,
		 tty->write_queue.len);
}

void tty_init()
{
  serial_init();
}
