/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

tp_obj cpuinfo_processor(TP);
tp_obj cpuinfo_vendor_id(TP);
tp_obj cpuinfo_cpu_family(TP);
tp_obj cpuinfo_model(TP);
tp_obj cpuinfo_model_name(TP);
tp_obj cpuinfo_stepping(TP);
tp_obj cpuinfo_flags(TP);
tp_obj cpuinfo_cpuinfo(TP);

static char *help =
	"Collection of routines to get cpu information.\n"
	"\n"
	"This exports:\n"
	"\t* cpuinfo.processor prints the processor id (only one is supported, so it's 0)\n"
	"\t* cpuinfo.vendor_id prints the vendor name\n"
	"\t* cpuinfo.model prints the model ID\n"
	"\t* cpuinfo.model_name prints the model name\n"
	"\t* cpuinfo.stepping prints the processor's stepping\n"
	"\t* cpuinfo.flags prints the flags processor\n"
	"\t* cpuinfo.cpuinfo prints all the information above\n";

void cpuinfo_init(TP)
{
	/* module */
	tp_obj cpuinfo_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, cpuinfo_mod, tp_string("processor"),
	       tp_fnc(tp, cpuinfo_processor));
	tp_set(tp, cpuinfo_mod, tp_string("vendor_id"),
	       tp_fnc(tp, cpuinfo_vendor_id));
	tp_set(tp, cpuinfo_mod, tp_string("cpu_family"),
	       tp_fnc(tp, cpuinfo_cpu_family));
	tp_set(tp, cpuinfo_mod, tp_string("model"),
	       tp_fnc(tp, cpuinfo_model));
	tp_set(tp, cpuinfo_mod, tp_string("model_name"),
	       tp_fnc(tp, cpuinfo_model_name));
	tp_set(tp, cpuinfo_mod, tp_string("stepping"),
	       tp_fnc(tp, cpuinfo_stepping));
	tp_set(tp, cpuinfo_mod, tp_string("flags"),
	       tp_fnc(tp, cpuinfo_flags));
	tp_set(tp, cpuinfo_mod, tp_string("cpuinfo"),
	       tp_fnc(tp, cpuinfo_cpuinfo));

	/* special attributes */
	tp_set(tp, cpuinfo_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, cpuinfo_mod, tp_string("__name__"), tp_string("cpuinfo"));
	tp_set(tp, cpuinfo_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("cpuinfo"), cpuinfo_mod);
}
