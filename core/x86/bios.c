/*
 * File: bios.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: dump the SMBIOS table
 */

#include <kernel/pyr0.h>
#include <kernel/bios.h>

#include <string.h>

static struct smbhdr smbhdr;

static int
verify_checksum(unsigned char *mem, int length)
{
	int i;
	unsigned char checksum = 0;

	for(i = 0; i < length; i++) {
		checksum += mem[i];
	}

	return checksum == 0;
}

int find_smbios_table()
{
	int length, i;

	unsigned char *mem = (unsigned char *) SMBIOS_START;
	char *sig = SMBIOS_SIGN;


	while ((unsigned int) mem < (SMBIOS_END + 1)) {
		memcpy(&smbhdr, mem, sizeof(smbhdr));

		if(strncmp(smbhdr.sig, sig, SMBIOS_SIGN_LEN) == 0) {
			if (verify_checksum(mem, smbhdr.len)) {
				break;
			}
		}
		mem += 16;
	}

	if ((unsigned int) mem == SMBIOS_END + 1) {
		return -1;
	}

	return 0;
}

