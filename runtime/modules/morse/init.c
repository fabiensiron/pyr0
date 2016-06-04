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

tp_obj morse_sos(TP);
tp_obj morse_say(TP);

static char *help =
	"Morse module for fun and profit :D\n"
	"\n"
	"This exports:\n"
	"\t* morse.sos says sos in morse.\n"
	"\t* morse.say says the string in morse.\n";

void morse_init(TP)
{
	/* module */
	tp_obj morse_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, morse_mod, tp_string("sos"), tp_fnc(tp, morse_sos));
	tp_set(tp, morse_mod, tp_string("say"), tp_fnc(tp, morse_say));

	/* special attributes */
	tp_set(tp, morse_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, morse_mod, tp_string("__name__"), tp_string("mem"));
	tp_set(tp, morse_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("morse"), morse_mod);
}
