/**
 * File: serial.h
 * Author: Fabien Siron <fabien.siron@epita.fr> 
 * 
 * Description: serial functions
 */

#ifndef _SERIAL_H_
# define _SERIAL_H_

/**
 * serial_init - init serial 1 and 2 at baudrate 38400
 */
void serial_init();

/**
 * serial_write - write on the serial line *index*
 *
 * @param index: COM ## index
 * @param buf: string to write
 * @param len: len of the string
 *
 * @return: len of the sent string
 */
ssize_t serial_write(u8 index, const char *buf, size_t len);

#endif /*!_SERIAL_H_*/
