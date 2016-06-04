/*
 * File: morse.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <kernel/pyr0.h>
#include <kernel/snd.h>
#include <kernel/pit.h>

tp_obj morse_sos(TP)
{
	sos();

	return tp_None;
}

static struct morse_alpha {
	char c;
	char buf[8];
} morse_alpha[] =  {
	/* letters */
	{'a', "01"},
	{'b', "1000"},
	{'c', "1010"},
	{'d', "100"},
	{'e', "0"},
	{'f', "0010"},
	{'g', "110"},
	{'h', "0000"},
	{'i', "00"},
	{'j', "0111"},
	{'k', "101"},
	{'l', "0100"},
	{'m', "11"},
	{'n', "10"},
	{'o', "111"},
	{'p', "0110"},
	{'q', "1101"},
	{'r', "010"},
	{'s', "000"},
	{'t', "1"},
	{'u', "001"},
	{'v', "0001"},
	{'w', "011"},
	{'x', "1001"},
	{'y', "1011"},
	{'z', "1100"},
	/* digits */
	{'1', "01111"},
	{'2', "00111"},
	{'3', "00011"},
	{'4', "00001"},
	{'5', "00000"},
	{'6', "10000"},
	{'7', "11000"},
	{'8', "11100"},
	{'9', "11110"},
	{'0', "11111"},
	{'\0', ""}
};

static void _long()
{
	long_beep();
	pit_wait(100);
}

static void _short()
{
	beep();
	pit_wait(100);
}

static void
_morse_say(char c)
{
	char *buf;
	int i;
	/* get letter */
	for (i = 0; morse_alpha[i].c != '\0'; i++) {
		if (morse_alpha[i].c == c)
			break;
	}

	if (morse_alpha[i].c != c)
		return;

	buf = morse_alpha[i].buf;

	for (;*buf != '\0'; ++buf) {
		switch(*buf) {
		case '1':
			_long();
			break;
		case '0':
			_short();
			break;
		}
	}
}

tp_obj morse_say(TP)
{
	tp_obj s = TP_TYPE(TP_STRING);
	const char *str = s.string.val;

	for(; *str != '\0'; ++str)
	{
		_morse_say(*str);
	}

	return tp_None;
}
