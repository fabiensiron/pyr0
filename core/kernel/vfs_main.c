/*
 * File: vfs_main.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <kernel/pyr0.h>
#include <kernel/vfs.h>

#include <string.h>

static struct vfs vfs;

# define MAX_FS     7

struct fs_vector {
	u8 size;
	struct fs fs[MAX_FS];
} fs_vector = {
	.size = 0,
};

int register_fs(struct fs *fs) {
	if (fs_vector.size == MAX_FS)
		return -1;

	memcpy(&fs_vector.fs[fs_vector.size], fs, sizeof(struct fs));
	fs_vector.size++;

	return 0;
}

struct fs *
find_fs(const char *name) {
	int i;
	for (i = 0; i < fs_vector.size; ++i) {
		if (strcmp(fs_vector.fs[i].name, name) == 0)
			return &fs_vector.fs[i];
	}

	return NULL;
}

void vfs_init(void) {
	/* instal fds */
	int i;

	fd_init();

	memset(&vfs.root, 0, sizeof(vfs.root));
	memset(&vfs.pwd, 0, sizeof(vfs.pwd));
}
