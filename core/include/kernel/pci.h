/**
 * File: pci.h
 * Author: Fabien Siron <fabien.siron@epita.fr> 
 */

#ifndef _PCI_H_
# define _PCI_H_

typedef int (* pci_hook)(u16 vendor_id, u16 device_id);

void pci_scan(pci_hook);

#endif /*_PCI_H_*/
