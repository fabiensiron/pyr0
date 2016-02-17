/**
 * File: serial.h
 * Author: Fabien Siron <fabien.siron@epita.fr> 
 * 
 * Description: serial functions
 */

#ifndef _SERIAL_H_
# define _SERIAL_H_

/**
 * serial_early_init - init serial 1 at baudrate 38400
 */
void serial_early_init();

/**
 * serial_init - init serial 2,3 and 4 at baudrate 38400
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
ssize_t serial_write(int index, const char *buf, size_t len);

#endif /*!_SERIAL_H_*/
