/*
 * File: morse.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <kernel/pyr0.h>
#include <kernel/snd.h>

tp_obj morse_sos(TP)
{
	sos();
  
	return tp_None;
}

tp_obj morse_say(TP)
{
	return tp_None;
}
