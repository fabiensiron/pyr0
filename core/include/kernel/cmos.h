/**
 * File: cmos.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#ifndef _PIT_H_
# define _PIT_H_

u32 read_cmos(void);

void get_time(u16 *hours, u16 *minutes, u16 *seconds);
void get_date(u16 *month, u16 *day);

#endif /*_PIT_H_*/
