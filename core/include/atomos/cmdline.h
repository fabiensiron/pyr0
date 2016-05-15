/*
 * File: cmdline.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: cmdline interface
 */

#ifndef _CMDLINE_H_
# define _CMDLINE_H_

#include <atomos/cmdline_list.h>

extern void cmdline_parse(char *cmdline, size_t cmdline_len);

#endif /*!_CMDLINE_H_*/
