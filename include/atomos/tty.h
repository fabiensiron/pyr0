/**
 * File: tty.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: terminal info
 */

#ifndef _TTY_H_
# define _TTY_H_

# define TTY_BUF_SIZE 1024

struct tty_queue
{
  unsigned long data;
  unsigned long len;
  char buf[TTY_BUF_SIZE];
};

struct tty
{
  void (*write)(struct tty *tty);
  struct tty_queue write_queue;
};

int tty_write(int c, const char *buf, size_t n);

void tty_init();

#endif /*_TTY_H_*/
