/*
 * File: vfs_main.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <kernel/pyr0.h>
#include <kernel/vfs.h>

static struct inode inode_array[INODE_ARRAY_LEN];
static struct filedesc fds;
static struct vfs vfs;

void vfs_init(void) {
	/* instal fds */
	int i;
	for (i = 0; i < FD_MAX; i++) {
		fds.files[i] = NULL;
	}
	vfs.root = NULL;
	vfs.pwd = NULL;
}
