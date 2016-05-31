/*
 * File: cpuinfo.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <string.h>

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <kernel/pyr0.h>
#include <kernel/cpuinfo.h>

static inline void
show_processor(void)
{
	printf("processor\t: 0\n");
}

static inline void
show_vendor_id(void)
{
	printf("vendor_id\t: %s\n", cpu_info.vendor);
}

static inline void
show_cpu_family(void)
{
	printf("cpu_family\t: %d\n", cpu_info.family_value);
}

static inline void
show_model(void)
{
	printf("model\t\t: %d\n", cpu_info.model_value);
}

static inline void
show_model_name(void)
{
	printf("model name\t: %s\n", cpu_info.model_name);
}

static inline void
show_stepping(void)
{
	printf("stepping\t: %d\n", cpu_info.stepping_value);
}

static inline void
show_flags(void)
{
	printf("flags\t\t: %s\n", cpu_info.cap);
}

tp_obj cpuinfo_processor(TP)
{
	show_processor();

	return tp_None;
}

tp_obj cpuinfo_vendor_id(TP)
{
	show_vendor_id();

	return tp_None;
}

tp_obj cpuinfo_cpu_family(TP)
{
	show_cpu_family();

	return tp_None;
}

tp_obj cpuinfo_model(TP)
{
	show_model();

	return tp_None;
}

tp_obj cpuinfo_model_name(TP)
{
	show_model_name();

	return tp_None;
}

tp_obj cpuinfo_stepping(TP)
{
	show_stepping();

	return tp_None;
}

tp_obj cpuinfo_flags(TP)
{
	show_flags();

	return tp_None;
}

tp_obj cpuinfo_cpuinfo(TP)
{
	show_processor();
	show_vendor_id();
	show_cpu_family();
	show_model();
	show_model_name();
	show_stepping();
	show_flags();

	return tp_None;
}
