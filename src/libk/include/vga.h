#ifndef VGA_H
#  define VGA_H

#include <stddef.h>
#include <stdint.h>

#include "../../libc/include/string.h"

// For now we work with constants. Of course, this should not stay like this.
// But until we can retrieve reasonable information about the graphics environment,
// we unfortunately can't avoid it.
#define FRONTBUFFER_ADDR 0xb8000
#define TUI_CELLS 80
#define TUI_ROWS 25

typedef uint8_t vga_attribute;
typedef uint16_t vga_char;

enum vga_color {
  // For foreground and background
  VGA_BLACK = 0,
  VGA_BLUE = 1,
  VGA_GREEN = 2,
  VGA_CYAN = 3,
  VGA_RED = 4,
  VGA_MAGENTA = 5,
  VGA_BROWN = 6,
  VGA_LIGHT_GREY = 7,
  // For foreground only
  VGA_DARK_GREY = 8,
  VGA_LIGHT_BLUE = 9,
  VGA_LIGHT_GREEN = 10,
  VGA_LIGHT_CYAN = 11,
  VGA_LIGHT_RED = 12,
  VGA_LIGHT_MAGENTA = 13,
  VGA_LIGHT_BROWN = 14,
  VGA_WHITE = 15,
};

#define vgacolor(fg, bg) ((fg) | ((bg) << 4))
#define vgachar(ch, color) ((ch) | ((color) << 8))
#define cursor(start, posx, posy) ((uint16_t*)((start) + ((posx) * CHARS * 2) + ((posx) * 2)))

extern void tui_initialize(void);
extern void tui_putch(char ch);
extern void tui_writeline(const char *str);
extern void tui_refresh(void);

#endif // VGA_H
