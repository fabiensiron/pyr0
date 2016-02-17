/*
 * File: kernel.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 * 
 * Description: Main kernel header
 */

#ifndef _KERNEL_H_
# define _KERNEL_H_

# include <atomos/types.h>
# include <atomos/panic.h>
# include <atomos/stddef.h>

# include "../../boot/multiboot.h"

void start_kernel (multiboot_info_t *);

# define KERN_ERR      0
# define KERN_WARNING  0
# define KERN_INFO     0
# define KERN_DEBUG    1
# define KERN_USER     2

int early_printk(const char *fmt, ...);
int printk(int level, const char *fmt, ...);

#endif /* !_KERNEL_H_ */
