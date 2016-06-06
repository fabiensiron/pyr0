/*
 * File: cpuinfo.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <string.h>
#include <stdlib.h>

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>
#include <tinypy/builtins.h>

#include <kernel/pyr0.h>
#include <kernel/bios.h>

tp_obj _smbios_bios(TP) {
	struct smbios_bios *smbios_tbl =
		(struct smbios_bios *)smbios_bios.data;
	tp_obj _smbios_bios_obj;
	/* XXX big memory leak: add to gc */
	char *vendor = malloc(80);
	char *version = malloc(80);
	char *release_date = malloc(80);

	_smbios_bios_obj = tp_object(tp);

	smbios_get_string(&smbios_bios, smbios_tbl->vendor,
			  vendor, 80);
	smbios_get_string(&smbios_bios, smbios_tbl->version,
			  version, 80);
	smbios_get_string(&smbios_bios, smbios_tbl->release,
			  release_date, 80);

	tp_set(tp, _smbios_bios_obj, tp_string("vendor"),
	       tp_string(vendor));
	tp_set(tp, _smbios_bios_obj, tp_string("version"),
	       tp_string(version));
	tp_set(tp, _smbios_bios_obj, tp_string("release"),
	       tp_string(release_date));
	tp_set(tp, _smbios_bios_obj, tp_string("__name__"),
	       tp_string("bios"));
	tp_set(tp, _smbios_bios_obj, tp_string("__doc__"),
	       tp_string("\t* bios.vendor\n"
			 "\t* bios.version\n"
			 "\t* bios.startaddr\n"
			 "\t* bios.release\n"
			 "\t* bios.romsize\n"
			 "\t* bios.char\n"
			 "\t* bios.charext\n"
			 "\t* bios.major_rel\n"
			 "\t* bios.minor_rel\n"
			 "\t* bios.ecf_major_rel\n"
			 "\t* bios.ecf_minor_rel\n"));

	return _smbios_bios_obj;
}

tp_obj _smbios_sys(TP) {
	struct smbios_sys *smbios_tbl =
		(struct smbios_sys *)smbios_sys.data;

	return tp_None;
}
