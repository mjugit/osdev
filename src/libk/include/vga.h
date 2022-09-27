#ifndef VGA_H
#  define VGA_H
#  include <stddef.h>
#  include <stdint.h>

#  include "kmem.h"
#  include "../../libc/include/string.h"

/* 
 * VGA constants
 * Notice: The screen resoution is not configured here. These are only
 * the values the library will use to calculate memory offsets.
 */
#  define VGA_COLS 80
#  define VGA_ROWS 25
#  define VGA_FRONTBUFF 0xb8000
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
  size_t tablen;
} vga_config;


/*
 * The distance between tabstopps.
 */
#  define TABLEN 10


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
				size_t rows,
				size_t tablen);

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

/*
 * vga_rotup
 * Rotates the backbuffer @nrows up, clearing @nrows at the bottom. It
 * also sets the cursor to the top of the freed space and returns its
 * new location.
 */
extern uint16_t *vga_rotup(size_t nrows);

/*
 * vga_printstr
 * Prints the \0 terminated string @str to the screen, beginning at
 * the current cursor location. All chars will be configured with the
 * default attributes.
 */
extern uint16_t *vga_printstr(const char *str);

/*
 * vga_newline
 * Sets the cursor to the first column of the next row. The screen
 * will be scrolled if theres no space left. Returns the new cursor
 * posititon.
 */
extern uint16_t *vga_newline(void);

/*
 * vga_tab
 * Moves the cursor to the next tabstop.
 */
extern uint16_t *vga_tab(void);

/*
 * vga_getrow
 * Returns the cursors y index.
 */
extern size_t vga_getrow(void);

/*
 * vga_getcol
 * Returns the cursors x index.
 */
extern size_t vga_getcol(void);

/*
 * vga_printhex
 * Prints @src in hex representation at the current cursor position.
 */
extern uint16_t *vga_printhex(uint32_t src);
/*
 * vga_printhex overloads for specific sizes;
 */
#  define vga_printhex32(src) vga_printhex(src)
#  define vga_printhex16(src) vga_printhex(((0xffff) & (src)))
#  define vga_printhex8(src) vga_printhex(((0xff) & (src)))

/*
 * vga_printuint
 * Prints @src in unsigned decimal representation at the current
 * cursor position.
 */
extern uint16_t *vga_printuint(uint32_t src);
/*
 * vga_printuint overloads for specific sizes;
 */
#  define vga_printuint32(src) vga_printuint(src)
#  define vga_printuint16(src) vga_printuint(((0xffff) & (src)))
#  define vga_printuint8(src) vga_printuint(((0xff) & (src)))

/*
 * vga_printint
 * Prints @src in decimal representation at the current cursor
 * position.
 */
extern uint16_t *vga_printint(int32_t src);
/*
 * vga_printint overloads for specific sizes;
 */
#  define vga_printint32(src) vga_printint(src)
#  define vga_printint16(src) vga_printint(((0xffff) & (src)))
#  define vga_printint8(src) vga_printint((0xff) & (src)))

/*
 * vga_printptr
 * Prints the address @src is pointing to.
 */
extern uint16_t *vga_printptr(void *ptr);


#endif
