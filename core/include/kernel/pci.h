/**
 * File: pci.h
 * Author: Fabien Siron <fabien.siron@epita.fr> 
 */

#ifndef _PCI_H_
# define _PCI_H_

const char *pci_vendor_lookup(u16 vendor_id);
const char *pci_device_lookup(u16 vendor_id, u16 device_id);

void pci_init(void);

#endif /*_PCI_H_*/
