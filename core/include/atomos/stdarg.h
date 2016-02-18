/*
 * File: stdarg.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

#ifndef _STDARG_H_
# define _STDARG_H_

# include <atomos/stddef.h>

typedef void* va_list;

# define ALIGN(type)							\
  (sizeof (type) +							\
   (sizeof (size_t) - (sizeof(type) % sizeof(size_t))) % sizeof(size_t))

# define va_start(ap, lastarg)			\
  (ap = (char *) &(lastarg) + ALIGN(lastarg))

# define va_arg(ap, type)				\
  (ap += ALIGN(type), *((type*) (ap - ALIGN(type))))

# define va_end(ap)				\
  ;

#endif /*!_STDARG_H_*/
