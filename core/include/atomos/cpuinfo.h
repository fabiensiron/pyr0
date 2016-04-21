#ifndef _CPUINFO_H_
# define _CPUINFO_H_

struct cpu_info {
	char vendor[13];
	char cap[512];
	unsigned int family_value;
	unsigned int model_value;
	unsigned int stepping_value;
	char model_name[80];
} cpu_info;

extern const char *feature_names[];

extern unsigned int cpuinfo_dump(void);

#endif /*!_CPUINFO_H_*/
