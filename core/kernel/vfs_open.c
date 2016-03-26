/*
 * File: vfs_open.c
 * Author: Fabien Siron <fabien.siron@epita.fr> 
 *             based on linux-0.01 release
 */

#include <atomos/fs.h>
#include <string.h>

struct file *filp[NR_OPEN];
struct file file_table[NR_FILE];

int sys_open(const char *name, int flags, int mode)
{
  struct file *f;
  int fd, i;
  
  for (fd = 0; fd< NR_OPEN; fd++)
    if (!filp[fd])
      break;

  if (fd>= NR_OPEN)
    return -1;

  f = file_table;
  for (i = 0; i < NR_FILE; i++,f++)
    if (!f->f_count)
      break;

  if (i>= NR_FILE)
    return -1;

  (filp[fd]=f)->f_count++;

  /* XXX: open namei */

  /* XXX: check for tty */

  f->f_flags = flags;
  f->f_count = 1;
  f->f_pos = 0;
  
  /* XXX: add mode and inode */

  return fd;
}

int sys_close(unsigned int fd)
{
  struct file *filp_;
    
  if (fd >= NR_OPEN)
    return -1;
  if (!(filp_ = filp[fd]))
    return -1;
  
  memset(filp[fd], 0, sizeof(struct file));
  
  if (filp_->f_count == 0)
    return -1;

  if (--filp_->f_count)
    return 0;

  /* XXX: free inodes */

  return 0;
}
