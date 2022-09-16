#ifndef VGA_H
#  define VGA_H
#  include <stddef.h>
#  include <stdint.h>

#  include "kmem.h"

/* 
 * VGA constants
 * Notice: The screen resoution is not configured here. These are only
 * the values the library will use to calculate memory offsets.
 */
#  define VGA_COLS 80
#  define VGA_ROWS 25
#  define FRONTBUFF 0xb8000

/*
 * The amount of background colors is limited, since there are only 3
 * bits to store it. The fourth bit indicates whether to blink. Using
 * one of the foreground colors will therefore result in a blinking
 * character instead of a brighter background.
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


/*
 * vga_ch
 * Combines a c char @ch and a set of vga attributes @attr to a vga
 * char.
 */
#  define vga_ch(ch, attr) ((ch) | ((attr) << 8))

/*
 * vga_attr
 * Combines a foreground color @fg and a background color @bg.
 */
#  define vga_attr(fg, bg) ((fg) | ((bg) << 4))


/*
 * vga_configure
 * Set the essential video options, that is the @frontbuff_ptr
 * (location of the frontbuffer), the @backbuff_ptr (location of the
 * backbuffer) and The amount of @cols and @rows (screen width and
 * height).
 */
extern vga_config vga_configure(uint16_t *frontbuff_ptr,
				 uint16_t *backbuff_ptr,
				 size_t cols,
				 size_t rows);

/*
 * vga_reset
 * Clears the screen and resets the cursor to 0/0.
 */
extern uint16_t *vga_reset(void);

/*
 * vga_setattr
 * Sets the default vga attributes to @attr. New haracters will
 * inherit this attributes.
 */
extern uint8_t vga_setattr(uint8_t attr);

/*
 * vga_tell
 * Returns a pointer to the cursor location in the backbuffer.
 */
extern uint16_t *vga_tell(void);

/*
 * vga_putch
 * Writes @ch to the screen at the current cursor location using the
 * default attributes.
 */
extern uint16_t *vga_putch(const char ch);

/*
 * vga_setcursor
 * Sets the cursor to @col x @row and returns the location where the
 * next char will be put at.
 */
extern uint16_t *vga_setcursor(size_t col, size_t row);

/*
 * vga_refresh
 * Synchronizes the frontbuffer with the backbuffer. In fact, this
 * function publishes the prepared changes to the user.
 */
extern uint16_t *vga_refresh(void);

/* vga_rotup
 * Rotates the backbuffer @nrows up, clearing @nrows at the bottom. It
 * also sets the cursor to the top of the freed space and returns its
 * new location.
 */
extern uint16_t *vga_rotup(size_t nrows);

#endif
