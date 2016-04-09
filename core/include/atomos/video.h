/*
 * File: video.h
 * Author: Fabien Siron <fabien.siron@epita.fr>
 *
 * Description: stuff about console and early console
 */

#ifndef _VIDEO_H_
# define _VIDEO_H_

# include <atomos/types.h>

# define CON_WIDTH 1024
# define CON_HEIGHT 768

# define CHAR_PER_LINE 80
# define CHAR_PER_COLUMN (CON_HEIGHT/12)

void video_putchar(int x, int y, char val);
void video_scroll(unsigned n);
int video_init(u32 physbase_);

#endif /*!_VIDEO_H_*/
