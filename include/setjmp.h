/*
 * File: setjmp.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: setjmp, actually use for exception handling in pyr0
 */

#ifndef _SETJMP_H_
# define _SETJMP_H_

typedef int jmp_buf[6];

/**
 * setjmp - setup the environment for a futur jump
 * @param env: is the jmp_buf env (which is actually the context)
 * 
 * @param ret: return 0 at first run, but val after the longjmp
 */
extern int setjmp(jmp_buf env);

/**
 * longjmp - jmp to the jump buf context
 * @param env: is the jmp_buf env (which is actually the context)
 * @param val: is the return value of the precedant setjmp.
 */
extern void longjmp(jmp_buf env, int val);

#endif /*!_SETJMP_H_*/
