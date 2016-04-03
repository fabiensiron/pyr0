/*
 * File: gets.c
 * Fabien Siron <fabien.siron@epita.fr>
 *
 * Desc: very unsafe, limit to 80 chars 
 */

#include <stdio.h>

#include <atomos/tty.h>

char *
gets(char *buf)
{
  char c; unsigned i;
  char *s;
  
  for (s = buf, i = 0; ((c = tty_getc()) != '\n') && i < 80; i++)
    *s++ = c;

  *s = '\0';
  
  return (buf);
}
