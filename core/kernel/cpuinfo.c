/*
 * This file is part of ToyOS and is released under the terms
 * of the NCSA / University of Illinois License - see LICENSE.md
 * Copyright (C) 2016 Fabien Siron <fabien.siron@epita.fr>
 *
 * cpuinfo
 *
 * Extract cpuinfo
 */

#include <string.h>
#include <atomos/cpuinfo.h>

const char *feature_names[] = {
	"fpu", "vme", "de", "pse", "tsc", "msr", "pae", "mce", "cx8",
	"apic", "", "sep", "mtrr", "pge", "mca", "cmov", "pat", "pse-36",
	"psn", "clfsh", "", "ds", "acpi", "mmx", "fxsr", "sse", "sse2",
	"ss", "htt", "tm", "ia64", "pbe", "sse3", "pclmulqdq", "dtes64",
	"monitor", "ds-cpl", "vmx", "smx", "est", "tm2", "ssse3", "cnxt-id",
	"sdbg", "fma", "cx16", "xtpr", "pdcm", "", "pcid", "dca", "sse4.1",
	"sse4.2", "x2apic", "movbe", "popcnt", "tsc-deadline", "aes",
	"xsave", "osxsave", "avx", "f17c", "rdrnd", "hypervisor"
};

static inline void
cpuid(unsigned int *eax, unsigned int *ebx,
      unsigned int *ecx, unsigned int *edx) {
	__asm__ __volatile__("cpuid"
			     : "=a" (*eax), "=b" (*ebx),
			       "=c" (*ecx), "=d" (*edx)
			     : "a" (*eax), "c"(0));
}

static void
get_cpu_vendor(void) {
	unsigned int a = 0x00000000;
	cpuid(&a,
	      (unsigned int *)&cpu_info.vendor[0],
	      (unsigned int *)&cpu_info.vendor[8],
	      (unsigned int *)&cpu_info.vendor[4]);
}

static void
get_cpu_cap(void) {
	unsigned int a = 0x00000001;
	unsigned int b,c,d, i = 0;
	char *it;
	cpuid(&a,(unsigned int *)&b, (unsigned int *)&c,
	      (unsigned int *)&d);

	for (i = 0, it = cpu_info.cap; i < 61 ;i++) {
		if (i < 32 && (d & (0x1 << i))) {
			size_t len = strlen(feature_names[i]);
			strcpy(it, feature_names[i]);
			it += len;
			*it = ' ';
			it++;
		} else if (i >= 32 && (c & ( 0x1 << (i-32)))) {
			size_t len = strlen(feature_names[i]);
			strcpy(it, feature_names[i]);
			it += len;
			*it = ' ';
			it++;
		}
	}
	*it = '\0';
}

static void
get_cpu_fms(void) {
	/* fms: family, model, stepping (intel application note 485) */
	unsigned int a = 0x00000001;
	unsigned int b,c,d;
	cpuid(&a,(unsigned int *)&b, (unsigned int *)&c,
	      (unsigned int *)&d);

	cpu_info.family_value = ((a >> 20) & 0xf) + ((a >> 8) & 0x7);
	cpu_info.model_value = (((a >> 16) & 0x7) << 4) + ((a >> 4) & 0x7);
	cpu_info.stepping_value = a & 0x7;
}

extern unsigned int cpuid_extended_check(void);

static void
get_cpu_model_name(void) {
	unsigned int a, a_;
	unsigned int b,c,d,i;
	char *it = cpu_info.model_name;
	if (!cpuid_extended_check()) {
		cpu_info.model_name[0] = '?';
		cpu_info.model_name[1] = '\0';
		return;
	}

	a_ = 0x80000002;
	for(a= a_, i = 0; i < 3; ++i, a = a_ + i) {
		cpuid(&a,(unsigned int *)&b, (unsigned int *)&c,
		      (unsigned int *)&d);

		memcpy(it, &a, sizeof(unsigned int));
		it += 4;
		memcpy(it, &b, sizeof(unsigned int));
		it += 4;
		memcpy(it, &c, sizeof(unsigned int));
		it += 4;
		memcpy(it, &d, sizeof(unsigned int));
		it += 4;
	}

}

extern unsigned int cpuid_check(void);

unsigned int cpuinfo_dump(void) {
	memset (&cpu_info, 0, sizeof(struct cpu_info));

	if (!cpuid_check())
		return -1;

	get_cpu_vendor();
	get_cpu_cap();
	get_cpu_fms();
	get_cpu_model_name();

	return 0;
}
