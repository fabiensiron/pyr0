/*
 * This header is automatically generated at build
 * Please, do not modify this file, modify modules_table_gen.pl instead.
 */

#ifndef _MODULES_H_
# define _MODULES_H_

#include <tinypy/tp.h>

extern void sh_init(TP);


void (*modules_init_vector[])(tp_vm *) = {
    sh_init,
    NULL,
};

#endif /*!_MODULES_H_*/