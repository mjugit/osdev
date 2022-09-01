#ifndef __VGA_H__
#  define __VGA_H__

#include <stdint.h>
#include <stddef.h>

#include "string.h"
#include "font.h"


// Framebuffer location
/* #define FBUFF 0xa0000 */
// Screen resolution
/* #define RESX 640 */
/* #define RESY 480 */

#define TBUFF 0xb8000
#define CHARS 80
#define LINES 25

#define vgacolor(fg, bg) ((fg) | ((bg) << 4))
#define vgachar(ch, color) ((ch) | ((color) << 8))
#define cursor(start, posx, posy) ((uint16_t*)((start) + ((posx) * CHARS * 2) + ((posx) * 2)))

extern void putchar(size_t posx, size_t posy, char ch);
extern void refresh(void);
extern void putstring(size_t posx, size_t posy, const char *str);


/* extern const uint16_t FONT_12x16[]; */

/* typedef uint32_t color_t; */
/* extern void putc(size_t posx, size_t posy, char ch, color_t color); */


#endif
