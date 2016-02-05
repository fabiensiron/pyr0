/*
 * File: vsprintf.c
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 */

# include <atomos/types.h>
# include <atomos/stdarg.h>
# include <atomos/string.h>

static
void uitoa(unsigned num, unsigned base, char **buf)
{
  int n = 0;
  unsigned int d = 1;
  if (base == 16)
    {
      *((*buf)++) = '0'; 
      *((*buf)++) = 'x';
    }
  
  while (num/d >= base)
    d*=base;
  while (d != 0)
    {
      int dgt = num / d;
      num %= d;
      d /= base;
      
      if (n || dgt > 0 || d == 0)
	{
	  *((*buf)++) = dgt + (dgt<10? '0' : ('a')-10);
	  ++n;
	}
    }
}

static
void itoa(int num, char **buf)
{
  if (num < 0)
    {
      num = -num;
      *((*buf)++) = '-';
    }
  uitoa(num, 10, buf);
}
# if 0
static
int sk_atoi(const char **s)
{
  int i = 0;

  while (**s >= '0' && **s <= '9')
    i = i*10 + *((*s)++) - '0';

  return i;
}
# endif
int vsprintf(char *buf, const char *fmt, va_list args)
{
  char *str;
  char *s;
  unsigned len, i;
  for (str=buf; *fmt; ++fmt)
    {
      if (*fmt != '%')
	{
	  *str = *fmt;
	  str++;
	}
      else
	{
	  //	  char lz = 0;
	  //	  char field_width = -1;
	  ++fmt;
	  //if (*fmt == '0')
	  //	    {
	  //	      lz = 1;
	  //	      ++fmt;
	  //	    }
	  //	  if (*fmt >= '0' && *fmt <= '9')
	  //	    {
	  //	      field_width = sk_atoi(&fmt);
	  //	    }
	  switch(*fmt)
	    {
	    case 'c':
	      *str++ = (unsigned char) va_arg(args, int);
	      
	      break;
	    case 's':
	      s = va_arg(args, char *);
	      if (!s)
		s = "<NULL>";
	      len = strlen(s);

	      for (i = 0; i < len; ++i)
		*str++ = *s++;

	      break;
	    case 'p':
	      uitoa(va_arg(args, unsigned long), 16, &str);
	      break;
	    case 'x':
	    case 'X':
	      uitoa(va_arg(args, unsigned long), 16, &str);
	      break;
	    case 'd':
	    case 'i':
	      itoa(va_arg(args, unsigned  long), &str);
	      break;
	    case 'u':
	      uitoa(va_arg(args, unsigned int), 10, &str);
	      break;
	    default:
	      if (*fmt != '%')
		*str++ = '%';
	      if (*fmt)
		*str++ = *fmt;
	      else
		--fmt;
	      
	      break;
	    }
	  
	}
    }
  *str = '\0';
  return str-buf;
}

int sprintf(char *buf, const char *fmt, ...)
{
  va_list args;
  int i;

  va_start(args, fmt);
  i = vsprintf(buf, fmt, args);
  va_end(args);
  
  return i;
}
