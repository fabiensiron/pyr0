/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <kernel/pyr0.h>
#include <kernel/cmos.h>

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

#define OS_NAME "pyr0"

tp_obj os_reboot(TP);
tp_obj os_halt(TP);
tp_obj os_loadkeys(TP);
tp_obj os_time(TP);
tp_obj os_date(TP);
tp_obj os_cmdline(TP);

static char *help =
	"OS routines for pyr0.\n"
	"\n"
	"This exports:\n"
	"\t* os.reboot which reboot the system\n"
	"\t* os.halt which quits the system\n"
	"\t* os.loadkeys loads the given keymap in graphical mode (\"dvorak\" or \"us\")\n"
	"\t* os.date prints the current date.\n"
	"\t* os.time prints the current time.\n"
	"\t* os.cmdline returns the core cmdline in a dictonary.\n";

void os_init(TP)
{
	/* module */
	tp_obj os_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, os_mod, tp_string("name"), tp_string(OS_NAME));
	tp_set(tp, os_mod, tp_string("reboot"), tp_fnc(tp, os_reboot));
	tp_set(tp, os_mod, tp_string("halt"), tp_fnc(tp, os_halt));
	tp_set(tp, os_mod, tp_string("loadkeys"), tp_fnc(tp, os_loadkeys));
	tp_set(tp, os_mod, tp_string("time"), tp_fnc(tp, os_time));
	tp_set(tp, os_mod, tp_string("date"), tp_fnc(tp, os_date));
	tp_set(tp, os_mod, tp_string("cmdline"), tp_fnc(tp, os_cmdline));

	/* special attributes */
	tp_set(tp, os_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, os_mod, tp_string("__name__"), tp_string("os"));
	tp_set(tp, os_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("os"), os_mod);
}
