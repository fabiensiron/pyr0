/*
 * File main.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: setup the operating system (mostly non arch-dependent) and 
 *   spawn the first process (init)
 */
#include <atomos/kernel.h>

void start_kernel(void)
{
  /* mem/paging */
  
  /* traps */

  /* irq */

  /* sched */
  
  /* command-line */

  /* buffer ? */

  /* time */

  /* move to user */
  /*
    if (!fork())
      init();

   */

  for (;;)
    ;
}

void init(void)
{
  /* setup video stuff and open tty1 */

  /* exec etc/init bin/init sbin/init */

  /* exec /bin/sh */

  /*
    if (!(pid=fork())) {
      close(0);
      execve("/bin/sh", _, _);
      _exit(2);
    }
    else if (pid>0)
      __wait__
    else
     error 
  _exit(0);
   */
}
