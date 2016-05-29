/**
 * File: pit.h
 * Author: Fabien Siron <fabien.siron@epita.fr> 
 */

#ifndef _PIT_H_
# define _PIT_H_

void pit_init(void);
unsigned long gettick(void);
void pit_wait(u32 duration);

#endif /*_PIT_H_*/
