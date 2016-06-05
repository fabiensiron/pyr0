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
static struct smbios_bios *smbios_bios;
static struct smbios_sys *smbios_sys;

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

int dump_smbios_entries()
{
	unsigned i, tcount = 1;
	struct smbtblhdr *smbtblhdr;
	u8 *addr, *end;

	addr = (u8 *)smbhdr.addr;
	end = (u8 *)smbhdr.addr + smbhdr.size;

	for (;addr + sizeof(struct smbtblhdr) < end &&
		     tcount <= smbhdr.count; tcount++)
	{
		smbtblhdr = (struct smbtblhdr *)addr;

		if (smbtblhdr->type == SMBIOS_TYPE_EOT) {
			break;
		} else if (smbtblhdr->type == SMBIOS_TYPE_BIOS) {
			smbios_bios =
				(struct smbios_bios *)
				(addr + sizeof(struct smbtblhdr));
		} else if (smbtblhdr->type == SMBIOS_TYPE_SYSTEM) {
			smbios_sys =
				(struct smbios_sys *)
				(addr + sizeof(struct smbtblhdr));
		}

		addr += smbtblhdr->size;
		for(; addr + 1 < end; addr++)
			if (*addr == 0 && *(addr + 1) == 0)
				break;

		addr += 2;
	}

	return 0;
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

