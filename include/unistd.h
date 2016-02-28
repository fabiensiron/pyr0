/*
 * File: unistd.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#ifndef _UNISTD_H_
#define _UNISTD_H_

# include <atomos/kernel.h>
# include <atomos/tty.h>

extern int close(int);
//extern off_t lseek(int, off_t, int);
extern ssize_t read(int, void *, size_t);

# define write(i, p, n)				\
  tty_write(KERN_INFO, p, n)

# define close() ((void)0) /* NOP */

#endif /* _UNISTD_H_ */
