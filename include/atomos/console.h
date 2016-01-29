/*
 * File: console.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: stuff about console and early console
 */

#ifndef _CONSOLE_H_
# define _CONSOLE_H_

# include <atomos/types.h>

/* early stuff */
void early_console_init (void);
int early_kdebug (const char *s, size_t length);

#endif /*!_CONSOLE_H_*/
