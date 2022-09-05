#ifndef VGA_H
#  define VGA_H

#include <stddef.h>
#include <stdint.h>

#include "../../libc/include/string.h"

#define TBUFF 0xb8000
#define CHARS 80
#define LINES 25

#define vgacolor(fg, bg) ((fg) | ((bg) << 4))
#define vgachar(ch, color) ((ch) | ((color) << 8))
#define cursor(start, posx, posy) ((uint16_t*)((start) + ((posx) * CHARS * 2) + ((posx) * 2)))

extern void putchar(size_t posx, size_t posy, char ch);
extern void refresh(void);
extern void putstring(size_t posx, size_t posy, const char *str);
extern void clear(void);

#endif // VGA_H
