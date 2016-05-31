/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

extern tp_obj sh_echo(TP);
extern tp_obj sh_yes(TP);

static char *help =
	"This module rules the pyr0's shell.\n"
	"\n"
	"This exports:\n"
	"\t* sh.echo echoes the user argument\n"
	"\t* sh.yes prints indefinitely \"yes\" or the given argument\n";

void sh_init(TP)
{
	/* module */
	tp_obj sh_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, sh_mod, tp_string("echo"), tp_fnc(tp, sh_echo));
	tp_set(tp, sh_mod, tp_string("yes"), tp_fnc(tp, sh_yes));

	/* special attributes */
	tp_set(tp, sh_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, sh_mod, tp_string("__name__"), tp_string("sh"));
	tp_set(tp, sh_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("sh"), sh_mod);
}
