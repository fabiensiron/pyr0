/*
 * File: math.c
 * Author: Luna Mendes <lkmnds@gmail.com>
 */
#include <string.h>

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <kernel/pyr0.h>

#include <math.h>

extern double sin(double num);

tp_obj math_sin(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = sin(x);
	return (tp_number(r));
}
