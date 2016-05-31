/*
 * File: os.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 */
#include <string.h>

#include <tinypy/tp.h>
#include <tinypy/dict.h>
#include <tinypy/string.h>

#include <kernel/pyr0.h>

tp_obj os_reboot(TP)
{
	reboot();

	return tp_None;
}

tp_obj os_halt(TP)
{
	reboot();

	return tp_None;
}

extern void kbd_set_keymap(u8 keymap_);

tp_obj os_loadkeys(TP)
{
	tp_obj s = TP_TYPE(TP_STRING);

	const char *c_s = s.string.val;

	if (strcmp(c_s, "dvorak") == 0)
		kbd_set_keymap(1);
	else if(strcmp(c_s, "us") == 0)
		kbd_set_keymap(0);
	else
		printf("Error: unknown keymap %s\n", c_s);

	return tp_None;
}

extern void get_date(unsigned short *month, unsigned short *day);

tp_obj os_date(TP)
{
	unsigned short month, day;

	get_date(&month, &day);

	printf("%u/%u\n", day, month);

	return tp_None;
}

extern void get_time(unsigned short *hours, unsigned short *minutes,
		     unsigned short *seconds);

tp_obj os_time(TP)
{
	unsigned short hours, minutes, seconds;

	get_time(&hours, &minutes, &seconds);

	printf("%u:%u:%u\n", hours, minutes, seconds);

	return tp_None;
}

