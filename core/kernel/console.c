/*
 * File: console.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: system console
 */

#include <kernel/video.h>
#include <kernel/console.h>

unsigned char console_is_init = 0;

struct {
	unsigned x;
	unsigned y;
} console_info =
{
	.x = 0,
	.y = 0,
};

/* console module */

void console_putchar(char n)
{
	/* special char */
	switch (n)
	{
	case '\b':
	{
		if (console_info.x == 0) {
			console_info.x = 0;
			if (console_info.y > 0)
				console_info.y -= 1;
		} else {
			console_info.x -= 1;
		}
		break;
	}
	case '\r':
	{
		console_info.x = 0;
		break;
	};
	case '\n':
	{
		console_info.y += 1;
		console_info.x = 0;
		break;
	}
	case '\t':
	{
		if (console_info.x + 4 < CHAR_PER_LINE)
			console_info.x += 4;
		break;
	}
	default:
	{
		video_putchar(console_info.x, console_info.y, ' ');
		video_putchar(console_info.x, console_info.y, n);
		console_info.y += (console_info.x + 1) / CHAR_PER_LINE;
		console_info.x = (console_info.x + 1) % CHAR_PER_LINE;
	}
	}

	if (console_info.y == CHAR_PER_COLUMN)
	{
		video_scroll(1);
		console_info.y--;
	}
}

size_t console_write(const char *buf, size_t len)
{
	unsigned i;

	for (i = 0; i< len; i++)
		console_putchar(buf[i]);

	return i;
}

void console_init()
{
	if (video_init(0) == -1)
		return;

	console_is_init = 1;
}
