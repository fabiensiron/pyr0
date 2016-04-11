/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

#define OS_NAME "pyr0"

tp_obj os_reboot(TP);
tp_obj os_halt(TP);
tp_obj os_loadkeys(TP);

void os_init(TP)
{
  /* module */
  tp_obj os_mod = tp_dict(tp);

  /* methods */
  tp_set(tp, os_mod, tp_string("name"), tp_string(OS_NAME));
  tp_set(tp, os_mod, tp_string("reboot"), tp_fnc(tp, os_reboot));
  tp_set(tp, os_mod, tp_string("halt"), tp_fnc(tp, os_halt));
  tp_set(tp, os_mod, tp_string("loadkeys"), tp_fnc(tp, os_loadkeys));

  /* special attributes */
  tp_set(tp, os_mod, tp_string("__doc__"),
	 tp_string("This module contains the OS routines."));
  tp_set(tp, os_mod, tp_string("__name__"), tp_string("os"));
  tp_set(tp, os_mod, tp_string("__file__"), tp_string(__FILE__));

  /* bind */
  tp_set(tp, tp->modules, tp_string("os"), os_mod);
}
