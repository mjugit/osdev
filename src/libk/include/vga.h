#ifndef VGA_H
#  define VGA_H
#  include <stddef.h>
#  include <stdint.h>

#  include "kmem.h"

// VGA constants
#  define VGA_COLS 80
#  define VGA_ROWS 25
#  define FRONTBUFF 0xb8000

/*
 * The amount of background colors is limited, since there
 * are only 3 bits to store it. The fourth bit indicates
 * whether to blink. Using one of the foreground colors will
 * therefore result in a blinking character instead of a
 * brighter one.
 */
typedef enum {
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
} vga_color;


typedef struct {
  uint16_t *frontbuff;
  uint16_t *backbuff;
  size_t sizex, sizey;
} vga_config;


#  define vga_ch(ch, attr) ((ch) | ((attr) << 8))
#  define vga_attr(fg, bg, blink) ((fg) | ((bg) << 4) | ((blink) << 7))

extern vga_config vga_initialize(uint16_t *frontbuff_ptr,
				 uint16_t *backbuff_ptr,
				 size_t cols,
				 size_t rows);

extern uint16_t *vga_reset(void);

extern uint8_t vga_setattr(uint8_t attr);

extern uint16_t *vga_tell(void);

extern uint16_t *vga_putch(const char ch);

#endif
