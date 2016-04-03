/*
 * File: sh.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

void sh_init(TP)
{
  /* module */
  tp_obj sh_mod = tp_dict(tp);

  /* special attributes */
  tp_set(tp, sh_mod, tp_string("__doc__"),
	 tp_string("This module rules the pyr0s shell."));
  tp_set(tp, sh_mod, tp_string("__name__"), tp_string("sh"));
  tp_set(tp, sh_mod, tp_string("__file__"), tp_string(__FILE__));

  /* bind */
  tp_set(tp, tp->modules, tp_string("sh"), sh_mod);
}
