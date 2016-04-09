/*
 * File: console.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: system console
 */

#include <atomos/video.h>
#include <atomos/console.h>

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
  video_putchar(console_info.x, console_info.y, ' ');
  video_putchar(console_info.x, console_info.y, n);
  console_info.y += (console_info.x + 1) / CHAR_PER_LINE;
  console_info.x = (console_info.x + 1) % CHAR_PER_LINE;

  if (console_info.y == CHAR_PER_COLUMN)
    {
      video_scroll(1);
      console_info.y--;
    }
}

void console_init()
{
  if (video_init(0) == -1)
    return;

  console_is_init = 1;
}
