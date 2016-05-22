/*
 * File: io.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: standard input/output in i386
 */

#ifndef _IOPORT_H_
# define _IOPORT_H_

# include <kernel/types.h>

static inline
void outb(u16 p, u8 v)
{
  __asm__ volatile("outb %0, %1\n"::"a" (v), "d" (p));
}

static inline
u8 inb(u16 p)
{
  u8 _v;
  __asm__ volatile("inb %1, %0\n": "=a" (_v): "d" (p));
  
  return _v;
}

static inline
void outw(u16 p, u16 v)
{
  __asm__ volatile("outw %0, %1\n":: "a" (v), "d" (p));
}

static inline
u16 inw(u16 p)
{
  u16 _v;
  __asm__ volatile("inw %1, %0\n": "=a" (_v): "d" (p));
  
  return _v;
}

#endif /*!_IOPORT_H_*/
