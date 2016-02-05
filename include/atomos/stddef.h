/*
 * File: stddef.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

#ifndef _STDDEF_H_
# define _STDDEF_H_

# ifndef _SIZE_T
#  define _SIZE_T
typedef unsigned int size_t;
# endif

# undef NULL
# define NULL ((void *) 0)

#endif /*!_STDDEF_H_*/
