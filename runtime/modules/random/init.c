/*
 * File: init.c
 * Author: Luna Mendes <lkmnds@gmail.com>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

#include "random.h"

static char *help =
	"Random routines of pyr0, equivalent of the random module in cpython.\n"
	"\n"
	"This exports:\n"
	"\t* random.random() - random number between [0,1]";

tp_obj rand_random(TP);

void random_init(TP)
{
	u32 cmos_time = read_cmos();
	sgenrand(cmos_time);
	/* module */
	tp_obj rand_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, rand_mod, tp_string("random"), tp_fnc(tp, rand_random));

	/* special attributes */
	tp_set(tp, rand_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, rand_mod, tp_string("__name__"), tp_string("random"));
	tp_set(tp, rand_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("random"), rand_mod);
}
