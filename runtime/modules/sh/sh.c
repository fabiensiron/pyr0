/*
 * File: sh.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <stdio.h>

tp_obj sh_echo(TP)
{
	tp_obj s = TP_TYPE(TP_STRING);

	return s;
}
tp_obj sh_yes(TP)
{
	tp_obj s = TP_DEFAULT(tp_string("yes"));

	while(1) {
		printf("%s\n", s.string.val);
	}

	return s;
}
