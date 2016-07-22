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

tp_obj math_sin(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = sin(x);
	return (tp_number(r));
}

tp_obj math_cos(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = cos(x);
	return (tp_number(r));
}

tp_obj math_tan(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = tan(x);
	return (tp_number(r));
}

tp_obj math_exp(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = exp(x);
	return (tp_number(r));
}

tp_obj math_ceil(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = ceil(x);
	return (tp_number(r));
}

tp_obj math_sqrt(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = sqrt(x);
	return (tp_number(r));
}

tp_obj math_acos(TP)
{
	double x = TP_NUM();
	double r = 0.0;
	r = acos(x);
	return (tp_number(r));
}
