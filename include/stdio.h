/*
 * File: stdio.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: minimal stdio for tinypy
 */

#ifndef _STDIO_H_
# define _STDIO_H_

# include <stdarg.h>
# include <atomos/kernel.h>

/* int printf(const char *fmt, ...); */

#define printf(fmt, ...)			\
  printk(KERN_INFO, fmt, ##__VA_ARGS__)

/* int fprintf(FILE *stream, const char *fmt, ...); */
#define printk(f, fmt, ...)			\
  printk(KERN_INFO,fmt, ##__VA_ARGS__)


extern int vsprintf(char *str, const char *fmt, va_list ap);
extern int vsnprintf(char *str, size_t size, const char *fmt, va_list ap);

#endif /*!_STDIO_H_*/
