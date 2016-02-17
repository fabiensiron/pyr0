/**
 * File: printk.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: printk and early_printk
 */

#include <atomos/kernel.h>
#include <atomos/serial.h>
#include <atomos/tty.h>
#include <atomos/stdarg.h>

extern int vsprintf(char *buf, const char *fmt, va_list args);

static char buf[1024];

static int (*early_write)(int, const char *, size_t) = serial_write;
static int (*write)(int, const char *, size_t) = tty_write;

int early_printk(const char *fmt, ...)
{
  va_list args;
  int i;

  va_start(args, fmt);
  i = vsprintf(buf, fmt, args);
  va_end(args);

  early_write(1, buf, i);

  return i;
}

int printk(int level, const char *fmt, ...)
{
  va_list args;
  int i;

  va_start(args, fmt);
  i = vsprintf(buf, fmt, args);
  va_end(args);

  write(level, buf, i);

  return i;
}
  
