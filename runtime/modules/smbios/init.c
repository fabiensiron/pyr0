/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

extern tp_obj _smbios_bios(TP);
extern tp_obj _smbios_sys(TP);

static char *help =
	"Dump of the smbios tables.\n"
	"\n"
	"This exports:\n"
	"\t* smbios.bios contains bios information.\n"
	"\t\t- smbios.bios.vendor\n"
	"\t\t- smbios.bios.version\n"
	"\t\t- smbios.bios.startaddr\n"
	"\t\t- smbios.bios.release\n"
	"\t\t- smbios.bios.romsize\n"
	"\t\t- smbios.bios.char\n"
	"\t\t- smbios.bios.charext\n"
	"\t\t- smbios.bios.major_rel\n"
	"\t\t- smbios.bios.minor_rel\n"
	"\t\t- smbios.bios.ecf_major_rel\n"
	"\t\t- smbios.bios.ecf_minor_rel\n"
	"\t* smbios.sys contains system information.\n "
	"\t\t- smbios.sys.vendor\n"
	"\t\t- smbios.sys.product\n"
	"\t\t- smbios.sys.version\n"
	"\t\t- smbios.sys.uuid\n"
	"\t\t- smbios.sys.wakeup\n"
	"\t\t- smbios.sys.sku\n"
	"\t\t- smbios.sys.family\n";

void smbios_init(TP)
{
	/* module */
	tp_obj smbios_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, smbios_mod, tp_string("bios"), tp_fnc(tp, _smbios_bios));
	tp_set(tp, smbios_mod, tp_string("sys"), tp_fnc(tp, _smbios_sys));

	/* special attributes */
	tp_set(tp, smbios_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, smbios_mod, tp_string("__name__"), tp_string("smbios"));
	tp_set(tp, smbios_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("smbios"), smbios_mod);
}
