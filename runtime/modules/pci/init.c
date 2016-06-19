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

#include "pci_list.h"

struct pci_ids_table *get_pci_elt(u16 vendor_id, u16 device_id) {
	struct pci_ids_table *it;
	for (it = pci_ids_table; it->ven_id < 0xffff; ++it) {
		if (it->ven_id == vendor_id) {
			if (it->dev_id == 0)
				return it;

			for (; it->ven_id == vendor_id; ++it) {
				if (it->dev_id == device_id)
					return it;
			}
		}
	}

	return NULL;
}

int hook(u16 vendor_id, u16 device_id)
{
	struct pci_ids_table *ids;

	ids = get_pci_elt(vendor_id, device_id);

	if (ids->ven_s == NULL || ids->dev_s == NULL)
		return -1;

	if (ids == NULL || (strlen(ids->ven_s) == 0 && strlen(ids->dev_s) == 0))
		printf("* %s: vendor<0x%x> device<0x%x>\n", ids->ven_s,
		       ids->ven_id, ids->dev_id);
	else
		printf("* %s: %s\n", ids->ven_s, ids->dev_s);

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
