/*
 * File: init.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/misc.h>

#include <kernel/pyr0.h>
#include <kernel/pci.h>

int hook(u16 vendor_id, u16 device_id)
{
	const char *vendor_s, *device_s;

	vendor_s = pci_vendor_lookup(vendor_id);
	device_s = pci_device_lookup(vendor_id, device_id);

	if (vendor_s == NULL || device_s == NULL)
		return -1;

	printf("* %s: %s\n", vendor_s, device_s);

	return 0;
}

tp_obj pci_show(TP)
{
	printf("PCI devices:\n");

	pci_scan(hook);

	return tp_None;
}

static char *help =
	"Show pci information.\n"
	"\n"
	"This exports:\n"
	"\t* pci.show shows pci devices.\n";

void pci_init(TP)
{
	/* module */
	tp_obj pci_mod = tp_dict(tp);

	/* methods */
	tp_set(tp, pci_mod, tp_string("show"), tp_fnc(tp, pci_show));

	/* special attributes */
	tp_set(tp, pci_mod, tp_string("__doc__"),
	       tp_string(help));
	tp_set(tp, pci_mod, tp_string("__name__"), tp_string("pci"));
	tp_set(tp, pci_mod, tp_string("__file__"), tp_string(__FILE__));

	/* bind */
	tp_set(tp, tp->modules, tp_string("pci"), pci_mod);
}
