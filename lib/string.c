/*
 * File: string.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mem and str operations
 */

#include <string.h>

void* memset (void* p, int c, size_t n) {
  char *src = p;

  c = (c & 0xff);

  while (n--)
    *src++ = c;

  return p;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
    const unsigned char*  p1   = s1;
    const unsigned char*  end1 = p1 + n;
    const unsigned char*  p2   = s2;
    int                   d = 0;

    for (;;) {
        if (d || p1 >= end1) break;
        d = (int)*p1++ - (int)*p2++;

        if (d || p1 >= end1) break;
        d = (int)*p1++ - (int)*p2++;

        if (d || p1 >= end1) break;
        d = (int)*p1++ - (int)*p2++;

        if (d || p1 >= end1) break;
        d = (int)*p1++ - (int)*p2++;
    }
    return d;
}

void* memcpy (void* dst_, const void* src_, size_t n) {
  const char *src = src_;
  char *dst = dst_;

  while (n--)
    *dst++ = *src++;

  return dst_;
}

void *memmove(void *dst_, const void *src_, size_t n)
{
  const char *src = src_;
  char *dst = dst_;

  if (!n)
    return dst_;

  if (dst_ <= src_)
    return memcpy(dst_, src_, n);

  src += n;
  dst += n;

  while (n--)
    *--dst = *--src;

  return dst_;
}


char* strcpy (char* dest, const char* src) {
  char* p = NULL;

  for (p = dest; *src != '\0'; p++, src++)
    *p = *src;

  *p = '\0';

  return dest;
}

int strcmp(const char* str1, const char* str2) {

  while (*str1 != '\0' && (*str1++ == *str2++));
  if ((*(unsigned char*)--str1) < (*(unsigned char*)--str2))
    return -1;
  return (*(unsigned char*)str1 != *(unsigned char*)str2);
}

size_t strlen (const char* str_) {
  const char *s;

  for (s = str_; *s; ++s)
    ;
  return (s - str_);
}

char *strchr(const char *p, int ch)
{
  for (;; ++p) {
    if (*p == ch)
      return((char *)p);
    if (!*p)
      return((char *)NULL);
  }
}

