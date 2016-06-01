/*
 * File: cmdline.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: cmdline interface
 */

#ifndef _CMDLINE_H_
# define _CMDLINE_H_

#include <kernel/cmdline_list.h>

void cmdline_parse (char *cmdline, size_t cmdline_len);
void cmdline_fill_opts (struct runtime_opt *opts);

char *get_var(int var);
char *get_str_arg(int var);

#endif /*!_CMDLINE_H_*/
