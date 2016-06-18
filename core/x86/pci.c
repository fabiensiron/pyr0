/*
 * File: pci.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

#include <kernel/pyr0.h>

#include <asm/io.h>

#include <misc/pci_list.h>

#define PCI_ADDRESS 0xCF8
#define PCI_VALUE   0xCFC

//typedef int (* pci_hook)(u8 bus, u8 device, u8 function, u8 reg);

static inline u32
make_pci_address(u8 bus, u8 device, u8 function, u8 reg) {
	return 0x80000000 | (bus << 16) | (device << 11) | (function << 8) |
		reg;
}

const char *
pci_vendor_lookup(u16 vendor_id) {
	unsigned int i;
	for (i = 0; i < PCI_VENTABLE_LEN; ++i) {
		if (PciVenTable[i].VenId == vendor_id) {
			return PciVenTable[i].VenFull;
		}
	}
	return "";
}

const char *
pci_device_lookup(u16 vendor_id, u16 device_id) {
	unsigned int i;
	for (i = 0; i < PCI_DEVTABLE_LEN; ++i) {
		if (PciDevTable[i].VenId == vendor_id &&
			PciDevTable[i].DevId == device_id) {
			return PciDevTable[i].ChipDesc;
		}
	}
	return "";
}

static void
pci_scan_slot(u8 bus, u8 slot) {
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

	/* XXX add multifunction devices */
}

void
pci_scan_bus(u8 bus) {
	unsigned i;
	for (i = 0; i < 32; ++i) {
		pci_scan_slot(bus, i);
	}
}

void pci_scan(void) {
	unsigned i;
	for (i = 0; i < 256; ++i) {
		pci_scan_bus(i);
	}
}
