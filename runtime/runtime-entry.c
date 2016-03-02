/*
 * File: runtime-entry.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <atomos/kernel.h>
#include <stdio.h>

#include <tinypy/tp.h>
#include <tinypy/vm.h>

void *code_p;
long code_l;

void start_runtime(void *p, long len, const char *name)
{
  printf("load %s!\n", name);
  code_p = p;
  code_l = len;

  /* init tinypy */
  char *argv[] = {"tinypy","hw.py"};
  tp_vm *tp = tp_init(2, argv);
  tp_ez_call(tp,"py2bc","tinypy",tp_None);
}
