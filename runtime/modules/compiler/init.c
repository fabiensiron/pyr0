/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

tp_obj compiler_tokenize(TP);

static char *help =
	"Compiler suite of Pyr0.\n"
	"\n"
	"This exports:\n"
	"\t* compiler.tokenize divides into tokens the src code\n";

void compiler_init(TP)
{
	/* module */
	tp_obj compiler_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, compiler_mod, tp_string("tokenize"),
	       tp_fnc(tp, compiler_tokenize));

	/* special attributes */
	tp_set(tp, compiler_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, compiler_mod, tp_string("__name__"), tp_string("compiler"));
	tp_set(tp, compiler_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("compiler"), compiler_mod);
}
