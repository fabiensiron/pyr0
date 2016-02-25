/*
 * File: irq.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: add or remove an interrupt handler
 */
#ifndef _IRQ_H_
# define _IRQ_H_

int setup_irq(unsigned int irq, void (*handler)(void));
void free_irq(unsigned int irq);
void init_IRQ(void);

#endif /*!_IRQ_H_*/
