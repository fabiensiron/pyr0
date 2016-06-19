/*
 * File: pci.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

#include <kernel/pyr0.h>
#include <kernel/pci.h>

#include <asm/io.h>

#define PCI_ADDRESS 0xCF8
#define PCI_VALUE   0xCFC

static inline u32
make_pci_address(u8 bus, u8 device, u8 function, u8 reg) {
	return 0x80000000 | (bus << 16) | (device << 11) | (function << 8) |
		reg;
}

static void
pci_scan_slot(pci_hook hook, u8 bus, u8 slot) {
	u16 vendor_id, device_id;
	const char *vendor_s, *device_s;
	u32 ids;
	u32 addr = make_pci_address(bus, slot, 0, 0);
	outl(PCI_ADDRESS, addr);

	ids = inl(PCI_VALUE);

	if ((ids >> 16) == 0xffff)
		return;

	vendor_id = ids;
	device_id = ids >> 16;

	hook(vendor_id, device_id);

	/* XXX add multifunction devices */
}

void
pci_scan_bus(pci_hook hook, u8 bus) {
	unsigned i;
	for (i = 0; i < 32; ++i) {
		pci_scan_slot(hook, bus, i);
	}
}

void pci_scan(pci_hook hook) {
	unsigned i;
	for (i = 0; i < 256; ++i) {
		pci_scan_bus(hook, i);
	}
}
