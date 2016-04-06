/*
 * File: os.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <atomos/kernel.h>

tp_obj os_reboot(TP)
{
  reboot();

  return tp_None;
}

tp_obj os_halt(TP)
{
  reboot();

  return tp_None;
}
