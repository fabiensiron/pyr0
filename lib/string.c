/*
 * File: string.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mem and str operations
 */

#include <atomos/string.h>

void* memset (void* p, int c, size_t n) {
  int* i = NULL;
  for (i = p; n > 0; n--, i++)
    *i = c;

  return p;
}

int memcmp (const void* p1, const void* p2, size_t n) {
  const int* i1 = NULL;
  const int* i2 = NULL;

  for (i1 = p1, i2 = p2; (*i1 == *i2) && n>0; n--, i1++, i2++)
    continue;

  return n;
}

void* memcpy (void* p1, const void* p2, size_t n) {
  char* i1 = NULL;
  const char* i2 = NULL;

  for (i1 = p1, i2 = p2; n>0; n--, i1++, i2++) 
    *(i1) = *(i2);

  return p1;
}

extern char* strcpy (char* dest, const char* src) {
  char* p = NULL;

  for (p = dest; *src != '\0'; p++, src++)
    *p = *src;

  *p = '\0';

  return dest;
}

extern int strcmp(const char* str1, const char* str2) {

  while (*str1 != '\0' && (*str1++ == *str2++));
  if ((*(unsigned char*)--str1) < (*(unsigned char*)--str2))
    return -1;
  return (*(unsigned char*)str1 != *(unsigned char*)str2);
}

extern int strlen (const char* str_) {
  int output = 0;
  int i;
  for (i = 0; str_[i] != '\0'; i++) 
    ++output;   
  return output;
}
