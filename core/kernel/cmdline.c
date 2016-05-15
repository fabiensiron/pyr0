/*
 * File: cmdline.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <atomos/kernel.h>
#include <atomos/cmdline.h>

#include <string.h>

/* XXX add cmdline variable spaces */

typedef enum {
	CMD_NULL = 0,
	CMD_BOOL = 1,
	CMD_INT,
	CMD_STRING,
} cmdline_type_t;

struct cmdline_mod_param {
	char var[80];
	cmdline_type_t type;
	unsigned char present;
	union {
		unsigned char b;
		unsigned int i;
		char s[80];
	} arg;
};

#include "cmdline_struct.h"

static int
wcmp(const char *str1, const char *str2) {
	while(*str1 != '\0' && *str1 != ' ' && *str1 != '=' &&
	      (*str1++ == *str2++));

	if ((*(unsigned char*)--str1) < (*(unsigned char *)--str2))
		return -1;

	return (*(unsigned char *)str1 != *(unsigned char *)str2);
}

static size_t
wlen(const char *str) {
	const char *s;

	for (s = str; *s && *s != ' ' && *s != '='; ++s)
		;

	return (s - str);
}

static size_t
lookup_var(const char *cmdline, int *var, size_t len) {
	struct cmdline_mod_param *mod_param_it;

	for (mod_param_it = mod_param, *var = 0;
	     mod_param_it->type != CMD_NULL;
	     ++mod_param_it, ++*var) {
		size_t var_len = wlen(mod_param_it->var);
		if (var_len > len)
			continue;

		if (wcmp(mod_param_it->var, cmdline) == 0) {
			return var_len;
		}
	}

	return 0;
}

static size_t
save_arg(const char *cmdline, int var, size_t len, size_t total_len) {
	size_t local_len = wlen(cmdline + len + 1);
	memcpy(mod_param[var].arg.s, cmdline + len + 1, local_len);
	mod_param[var].arg.s[local_len] = '\0';
	mod_param[var].present = 1;

	return local_len;
}

char *
get_str_arg (int var) {
	if (!mod_param[var].present)
		return NULL;

	return mod_param[var].arg.s;
}

int
get_integer_arg (int var) {
	/* TODO */
	if (!mod_param[var].present)
		return -1;

	return 0;
}

unsigned char
get_boolean_arg (int var) {
	/* TODO */
	if (!mod_param[var].present)
		return 0;

	return 0;
}

void cmdline_parse(char *cmdline, size_t cmdline_len)
{
	size_t len, offset = 0;
	int var;

	/* skip first */
	len = wlen(cmdline);
	cmdline += (len + 1);
	offset += (len + 1);

	do {
		len = lookup_var(cmdline, &var, cmdline_len - offset);

		if (len == 0)
			return;
		len += save_arg(cmdline, var, len, cmdline_len - offset);

		offset += (len + 2);
		cmdline += (len + 2);
	} while(offset < cmdline_len);
}
