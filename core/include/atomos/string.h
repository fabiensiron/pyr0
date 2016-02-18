/*
 * File: string.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: mem and str operations
 */

#ifndef _STRING_H_
# define _STRING_H_

# include <atomos/kernel.h>

void* memset (void*, int, size_t);
int memcmp (const void*, const void*, size_t);
void* memcpy (void*, const void*, size_t);
extern char* strcpy (char*, const char*);
extern int strcmp (const char*, const char*);
extern int strlen (const char*);

#endif /*!_STRING_H_*/
