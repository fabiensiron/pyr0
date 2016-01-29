#include <asm/io.h>
#include <atomos/types.h>
#include <atomos/console.h>

#define FB_BEGIN 0xB8000
#define FB_END   0xB8FA0

#define FB_WIDTH  80
#define FB_HEIGHT 25

struct
{
  size_t x;
  size_t y;
} s_current_position;


char *fb = (void *) FB_BEGIN;

static inline
void set_character(const char a, unsigned char x, unsigned char y)
{
  fb[(y * FB_WIDTH + x) * 2] = a;
}

static
void set_cursor (unsigned x, unsigned y)
{
  unsigned short position=(y*80) + x;

  // cursor LOW port to vga INDEX register
  outb(0x3D4, 0x0F);
  outb(0x3D5, (unsigned char )(position&0xFF));
  // cursor HIGH port to vga INDEX register
  outb(0x3D4, 0x0E);
  outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

static
void clear()
{
  char *it;
  for (it = fb; it < (char *)FB_END; it = it + 2)
    {
      *it = ' ';
      //      *(it + 1) = e_background_color << 4 | e_foreground_color;
    }

  s_current_position.x = 0;
  s_current_position.y = 0;
  set_cursor (s_current_position.x, s_current_position.y);
}

static
void putc (const char c)
{
  /* manage special characters */
  switch (c)
    {
    case '\n':
      s_current_position.y += 1;
      set_cursor (s_current_position.x, s_current_position.y);
    case '\r':
      s_current_position.x = 0;
      set_cursor (0, s_current_position.y); return;
    case '\t': early_kdebug ("        ", 8); return;
    }
  /* manage simple characters */
  //  set_color (e_background_color, e_foreground_color, s_current_position.x,
  //	     s_current_position.y);
  set_character (c, s_current_position.x, s_current_position.y);  
  s_current_position.y += (s_current_position.x + 1) / FB_WIDTH;
  s_current_position.x = (s_current_position.x + 1) % FB_WIDTH;

  set_cursor (s_current_position.x, s_current_position.y);
}

int early_kdebug (const char* s, size_t length)
{
  size_t i;

  for (i = 0;s[i] != '\0' && i < length; i++)
      putc (s[i]);

  return i;
}

void early_console_init ()
{
  s_current_position.x = 0;
  s_current_position.y = 0;

  set_cursor (0, 0);

  clear ();
}
