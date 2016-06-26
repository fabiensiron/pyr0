#ifndef _BIOSVAR_H_
#define _BIOSVAR_H_

#include <kernel/pyr0.h>

#define SMBIOS_START			0xf0000
#define SMBIOS_END			0xfffff

#define SMBIOS_SIGN                     "_SM_"
#define SMBIOS_SIGN_LEN                  4

struct smbhdr {
	char	sig[4];		/* "_SM_" */
	u8	checksum;	/* Entry point checksum */
	u8	len;		/* Entry point structure length */
	u8	majrev;		/* Specification major revision */
	u8	minrev;		/* Specification minor revision */
	u16	mss;		/* Maximum Structure Size */
	u8	epr;		/* Entry Point Revision */
	u8	fa[5];		/* value determined by EPR */
	u8	sasig[5];	/* Secondary Anchor "_DMI_" */
	u8	sachecksum;	/* Secondary Checksum */
	u16	size;		/* Length of structure table in bytes */
	u32	addr;		/* Structure table address */
	u16	count;		/* Number of SMBIOS structures */
	u8	rev;		/* BCD revision */
} __attribute__((packed));

struct smbtblhdr {
	u8	type;
	u8	size;
	u16	handle;
} __attribute__((packed));

struct smbtable {
	struct smbtblhdr *hdr;
	void		 *tblhdr;
	u32	 cookie;
};

#define	SMBIOS_TYPE_BIOS		0
#define	SMBIOS_TYPE_SYSTEM		1
#define	SMBIOS_TYPE_BASEBOARD		2
#define	SMBIOS_TYPE_ENCLOSURE		3
#define	SMBIOS_TYPE_PROCESSOR		4
#define	SMBIOS_TYPE_MEMCTRL		5
#define	SMBIOS_TYPE_MEMMOD		6
#define	SMBIOS_TYPE_CACHE		7
#define	SMBIOS_TYPE_PORT		8
#define	SMBIOS_TYPE_SLOTS		9
#define	SMBIOS_TYPE_OBD			10
#define	SMBIOS_TYPE_OEM			11
#define	SMBIOS_TYPE_SYSCONFOPT		12
#define	SMBIOS_TYPE_BIOSLANG		13
#define	SMBIOS_TYPE_GROUPASSOC		14
#define	SMBIOS_TYPE_SYSEVENTLOG		15
#define	SMBIOS_TYPE_PHYMEM		16
#define	SMBIOS_TYPE_MEMDEV		17
#define	SMBIOS_TYPE_ECCINFO32		18
#define	SMBIOS_TYPE_MEMMAPARRAYADDR	19
#define	SMBIOS_TYPE_MEMMAPDEVADDR	20
#define	SMBIOS_TYPE_INBUILTPOINT	21
#define	SMBIOS_TYPE_PORTBATT		22
#define	SMBIOS_TYPE_SYSRESET		23
#define	SMBIOS_TYPE_HWSECUIRTY		24
#define	SMBIOS_TYPE_PWRCTRL		25
#define	SMBIOS_TYPE_VOLTPROBE		26
#define	SMBIOS_TYPE_COOLING		27
#define	SMBIOS_TYPE_TEMPPROBE		28
#define	SMBIOS_TYPE_CURRENTPROBE	29
#define	SMBIOS_TYPE_OOB_REMOTEACCESS	30
#define	SMBIOS_TYPE_BIS			31
#define	SMBIOS_TYPE_SBI			32
#define	SMBIOS_TYPE_ECCINFO64		33
#define	SMBIOS_TYPE_MGMTDEV		34
#define	SMBIOS_TYPE_MGTDEVCOMP		35
#define	SMBIOS_TYPE_MGTDEVTHRESH	36
#define	SMBIOS_TYPE_MEMCHANNEL		37
#define	SMBIOS_TYPE_IPMIDEV		38
#define	SMBIOS_TYPE_SPS			39
#define	SMBIOS_TYPE_INACTIVE		126
#define	SMBIOS_TYPE_EOT			127

struct smbios_bios {
	u8 vendor;
	u8 version;
	u16 startaddr;
	u8 release;
	u8 romsize;
	u32 char1;
	u32 char2;
	u32 charext;
	u8 major_rel;
	u8 minor_rel;
	u8 ecf_major_rel;
	u8 ecf_minor_rel;
} __attribute__((packed));

struct smbios_sys {
	u8 vendor;
	u8 product;
	u8 version;
	u8 serial;
	u8 uuid[16];
	u8 wakeup;
	u8 sku;
	u8 family;
} __attribute__((packed));

struct smbios_entry {
	struct smbtblhdr hdr;
	u32 data;
	u32 strings;
};

extern struct smbios_entry smbios_bios;
extern struct smbios_entry smbios_sys;

//int find_smbios_table(void);
char *smbios_get_string(struct smbios_entry *entry, u8 indx, char *dest,
	size_t len);
int probe_and_dump_smbios();

void bios_early_init();
u32 bios_get_ebda();

#endif /* _BIOSVAR_H_ */
