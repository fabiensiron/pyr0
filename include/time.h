/*
 * File: time.h
 * Author: fabien.siron@epita.fr
 */
#ifndef _TIME_H_
#define _TIME_H_

#include <atomos/kernel.h>

#define CLOCKS_PER_SEC     1000000

typedef long clock_t ;
//extern clock_t   clock(void);
# define clock() (0)

#endif /* _TIME_H_ */
