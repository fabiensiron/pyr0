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
