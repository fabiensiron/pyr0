/*
 * File: vfs_utils.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <kernel/pyr0.h>
#include <kernel/vfs.h>

#include <string.h>

static struct inode inode_array[INODE_ARRAY_LEN];

#define IS_INO_PRESENT(x) ((x)->present)

struct inode *default_alloc_inode()
{
	int i;
	for (i = 0; i < INODE_ARRAY_LEN; ++i)
	{
		if (!IS_INO_PRESENT(&inode_array[i])) {
			inode_array[i].present = 1;
			return &inode_array[i];
		}
	}

	return NULL;
}

void default_delete_inode(struct inode *i)
{
	memset(i, 0, sizeof(struct inode));
}

void default_init_inode()
{
	int i;
	for (i = 0; i < INODE_ARRAY_LEN; ++i)
		memset(inode_array, 0, INODE_ARRAY_LEN);
}

static struct filedesc fds;

static int fd_get_empty() {
	int i;
	for (i = 0; i < FD_MAX; ++i) {
		if (!fds.files[i])
			break;
	}

	if (i == FD_MAX)
		return -1;

	return i;
}

int fd_file_install (struct file *file) {
	int fd = fd_get_empty();

	if (fd == -1) return -1;

	fds.files[fd] = file;

	return fd;
}

struct file *fd_file_get (int fd) {
	return fds.files[fd];
}

void fd_file_release (int fd) {
	struct file *f = fd_file_get(fd);

	/* vfs_close f */

	fds.files[fd] = NULL;
}

void fd_init () {
	int i;
	for (i = 0; i < FD_MAX; i++) {
		fds.files[i] = NULL;
	}
}
