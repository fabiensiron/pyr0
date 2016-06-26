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
struct smbios_entry smbios_bios;
struct smbios_entry smbios_sys;

u32 ebda_addr;
u32 mem_top;

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
			memcpy(&smbios_bios.hdr, addr,
			       sizeof(struct smbtblhdr));

			smbios_bios.data =
				(u32) (addr + sizeof(struct smbtblhdr));
			smbios_bios.strings =
				(u32) (addr + smbtblhdr->size);

		} else if (smbtblhdr->type == SMBIOS_TYPE_SYSTEM) {
			memcpy(&smbios_sys.hdr, addr,
			       sizeof(struct smbtblhdr));

			smbios_sys.data =
				(u32) (addr + sizeof(struct smbtblhdr));
			smbios_sys.strings =
				(u32) (addr + smbtblhdr->size);
		}

		addr += smbtblhdr->size;
		for(; addr + 1 < end; addr++)
			if (*addr == 0 && *(addr + 1) == 0)
				break;

		addr += 2;
	}

	return 0;
}

char *smbios_get_string(struct smbios_entry *entry, u8 indx, char *dest,
			size_t len)
{
	u8 *addr, *end;
	int i;
	char *ret = NULL;

	addr = (u8 *)entry->strings;
	end = (u8 *)smbhdr.addr + smbhdr.size;

	for (i = 1; addr < end && i < indx && *addr; i++)
		while(*addr++)
			;

	if (i == indx) {
		if (addr + len < end) {
			ret = dest;
			memcpy(ret, addr, len);
			ret[len - 1] = '\0';
		}
	}

	return ret;
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

int probe_and_dump_smbios() {
	if (find_smbios_table() == -1)
		return -1;

	return dump_smbios_entries();
}



void bios_early_init()
{
#define EBDA_BASE_ADDRESS 0x40E
#define MEM_TOP 0x413
	ebda_addr = *((u16 *)EBDA_BASE_ADDRESS) << 4;
	mem_top = *((u16 *)MEM_TOP) << 10;
}

u32 bios_get_ebda()
{
	return ebda_addr;
}

u32 bios_get_memtop()
{
	return mem_top;
}
