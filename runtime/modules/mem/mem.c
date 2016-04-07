/*
 * File: mem.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <atomos/kernel.h>

extern void *brk_base;
extern void *brk_limit;

extern void *sbrk(ssize_t inc);

tp_obj mem_brk(TP)
{
  u32 ret = (u32)sbrk(0);
  
  return tp_number(ret);
}

tp_obj mem_used(TP)
{
  u32 ret = (u32)sbrk(0);
  ret -= (u32)brk_base;

  return tp_number(ret);
}

tp_obj mem_available(TP)
{
  u32 ret = (u32)sbrk(0);
  ret = (u32)brk_limit - (u32)ret;

  return tp_number(ret);
}

tp_obj mem_len(TP)
{
  u32 ret = (u32)brk_limit - (u32)brk_base;

  return tp_number(ret);
}
