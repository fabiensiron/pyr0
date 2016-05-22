/*
 * File: vfs.h
 * Author: Fabien Siron <fabiensiron@orange.fr>
 */

#ifndef _VFS_H_
# define _VFS_H_

# include <kernel/pyr0.h>

struct fops;
struct iops;

struct inode {
	char name[256];
	ino_t ino;
	size_t size;

	struct inode *first_son;
	struct inode *next_brother;

	const struct fops *fops;
	const struct iops *iops;

	void *data;
};

struct file {
	off_t offset;
	int mode;
	int flags;

	struct inode *inode;
	size_t refcnt;

	const struct fops *fops;

	void *data;
};

struct fops {
	int (*open)(struct inode*, struct file*);
	ssize_t (*read)(struct file *, char *, size_t);
	ssize_t (*write)(struct file *, const char *, size_t);
	off_t (*lseek)(struct file *, off_t, int);
	void (*release)(size_t);
};

struct iops {
	struct inode (*lookup)(struct inode*, char *);
	int (*unlink)(struct inode*);
};

# define INODE_ARRAY_LEN 1024
# define FD_MAX 256

struct filedesc {
	struct file *files[FD_MAX];
};

struct fs {
	const char name[32];
	struct fops fops;
};

struct vfs {
	struct inode root;
	struct inode pwd;
};

void vfs_init(void);

#endif /*!_VFS_H_*/
