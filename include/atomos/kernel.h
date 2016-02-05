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


void start_kernel (void);

#endif /* !_KERNEL_H_ */
