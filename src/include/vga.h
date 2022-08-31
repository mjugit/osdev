#ifndef __VGA_H__
#  define __VGA_H__

#include <stdint.h>
#include <stddef.h>

#include "string.h"
#include "font.h"


// Framebuffer location
#define FBUFF 0xa0000
// Screen resolution
#define RESX 640
#define RESY 480

extern const uint16_t FONT_12x16[];

typedef uint32_t color_t;

extern void putc(size_t posx, size_t posy, char ch, color_t color);

#endif
