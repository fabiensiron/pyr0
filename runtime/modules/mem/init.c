/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

tp_obj mem_brk(TP);
tp_obj mem_used(TP);
tp_obj mem_available(TP);
tp_obj mem_len(TP);

void mem_init(TP)
{
  /* module */
  tp_obj mem_mod = tp_dict(tp);

  /* methods */
  tp_set(tp, mem_mod, tp_string("get_brk"), tp_fnc(tp, mem_brk));
  tp_set(tp, mem_mod, tp_string("used"), tp_fnc(tp, mem_used));
  tp_set(tp, mem_mod, tp_string("available"), tp_fnc(tp, mem_available));
  tp_set(tp, mem_mod, tp_string("len"), tp_fnc(tp, mem_len));

  /* special attributes */
  tp_set(tp, mem_mod, tp_string("__doc__"),
	 tp_string("This module contains debug routines for dynamic"
		   "memory allocation (malloc/free)."));
  tp_set(tp, mem_mod, tp_string("__name__"), tp_string("mem"));
  tp_set(tp, mem_mod, tp_string("__file__"), tp_string(__FILE__));

  /* bind */
  tp_set(tp, tp->modules, tp_string("mem"), mem_mod);
}
