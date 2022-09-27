#include "include/vga.h"

static vga_config _config;
static uint8_t _defaultattr;
static size_t _cursorx, _cursory;

/*
 * vga_configure
 * Set the essential video options, that is the @frontbuff_ptr (location of
 * the frontbuffer), the @backbuff_ptr (location of the backbuffer) and The
 * amount of @cols and @rows (screen width and height). 
 */
vga_config vga_configure(uint16_t *frontbuff_ptr,
			 uint16_t *backbuff_ptr,
			 size_t cols,
			 size_t rows,
			 size_t tablen) {
  _config = (vga_config) {
    .frontbuff = frontbuff_ptr,
    .backbuff = backbuff_ptr,
    .sizex = cols,
    .sizey = rows,
    .tablen = tablen
  };

  return _config;
}

/*
 * vga_reset
 * Clears the screen and resets the cursor to 0/0.
 */
uint16_t *vga_reset(void) {
  kmemset16(_config.backbuff, 0x00, _config.sizex * _config.sizey);
  _cursorx = _cursory = 0;

  return vga_tell();
}

/*
 * vga_setattr
 * Sets the default vga attributes to @attr. New haracters will inherit this
 * attributes.
 */
uint8_t vga_setattr(uint8_t attr) {
  _defaultattr = attr;

  return _defaultattr;
}

/*
 * vga_tell
 * Returns a pointer to the cursor location in the backbuffer.
 */
uint16_t *vga_tell(void) {
  return &(_config.backbuff[_cursory * _config.sizex + _cursorx]);
}

/*
 * vga_putch
 * Writes @ch to the screen at the current cursor location using the default
 * attributes.
 */
uint16_t *vga_putch(const char ch) {
  uint16_t *cursor = vga_tell();

  switch (ch) {
  case '\n':
    vga_newline();
    break;

  case '\t':
    vga_tab();
    break;

  default:
    *cursor = vga_ch(ch, _defaultattr);
    _cursorx++;
    
    if (_cursorx > _config.sizex - 1) {
      _cursory++;
      _cursorx = 0;

      if (_cursory > _config.sizey - 1)
	vga_rotup(1);
    }

    break;
  }
  
  return vga_tell();
}

/*
 * vga_setcursor
 * Sets the cursor to @col x @row and returns the location where the
 * next char will be put at.
 */
uint16_t *vga_setcursor(size_t col, size_t row) {
  _cursorx = col;
  _cursory = row;

  return vga_tell();
}

/*
 * vga_refresh
 * Synchronizes the frontbuffer with the backbuffer. In fact, this
 * function publishes the prepared changes to the user.
 */
uint16_t *vga_refresh(void) {
  kmemcpy(_config.frontbuff, _config.backbuff,
	  sizeof(uint16_t) * _config.sizex * _config.sizey);

  return vga_tell();
}

/* vga_rotup
 * Rotates the backbuffer @nrows up, clearing @nrows at the bottom. It
 * also sets the cursor to the top of the freed space and returns its
 * new location.
 */
uint16_t *vga_rotup(size_t nrows) {
  uint16_t *areastart = vga_setcursor(0, nrows);
  size_t nbytes = (_config.sizey - nrows) * _config.sizex * sizeof(uint16_t);

  kmemcpy(_config.backbuff, areastart, nbytes);

  uint16_t *areaend = vga_setcursor(0, _config.sizey - nrows);
  kmemset16(areaend, 0, _config.sizex * nrows);

  vga_setcursor(0, _config.sizey - nrows);
  
  return vga_tell();
}

/*
 * vga_print
 * Prints the \0 terminated string @str to the screen, beginning at
 * the current cursor location. All chars will be configured with the
 * default attributes.
 */
uint16_t *vga_printstr(const char *str) {
  while (*str)
    vga_putch(*str++);

  return vga_tell();
}

/*
 * vga_newline
 * Sets the cursor to the first column of the next row. The screen
 * will be scrolled if theres no space left.
 */
uint16_t *vga_newline(void) {
  _cursorx = 0;
  _cursory++;

  if (_cursory > _config.sizey - 1)
    vga_rotup(1);

  return vga_tell();
}

/*
 * vga_tab
 * Moves the cursor to the next tabstop.
 */
uint16_t *vga_tab(void) {
  size_t nexttabstop = (((_cursorx / TABLEN) + 1) * TABLEN) - 1;
  if (nexttabstop >= _config.sizex - 1) {
    size_t remaining = nexttabstop - _config.sizex;
    _cursory++;
    _cursorx = remaining;
  } else {
    _cursorx = nexttabstop;
  }
  
  return vga_setcursor(_cursorx, _cursory);
}

/*
 * vga_getrow
 * Returns the cursors y index.
 */
size_t vga_getrow(void) {
  return _cursory;
}

/*
 * vga_getcol
 * Returns the cursors x index.
 */
size_t vga_getcol(void) {
  return _cursorx;
}

/*
 * vga_printhex
 * Prints @src in hex representation at the current cursor position.
 */
uint16_t *vga_printhex(uint32_t src) {
  char glyphbuff[64] = { 0 };
  char glyphs[] = "0123456789abcdef";

  glyphbuff[63] = '\0';
  char *glyphptr = &glyphbuff[62];

  while (src > 0) {
    char nextglyph = glyphs[src % 16];
    src /= 16;
    *glyphptr-- = nextglyph;
  }

  *glyphptr-- = 'x'; 
  *glyphptr = '0';
  
  vga_printstr(glyphptr);

  return vga_tell();
}

/*
 * vga_printuint
 * Prints @src in unsigned decimal representation at the current
 * cursor position.
 */
uint16_t *vga_printuint(uint32_t src) {
  char glyphbuff[64] = { 0 };
  char glyphs[] = "0123456789";

  glyphbuff[63] = '\0';
  char *glyphptr = &glyphbuff[63];
  
  while (src > 0) {
    glyphptr--;
    char nextglyph = glyphs[src % 10];
    src /= 10;
    *glyphptr = nextglyph;
  }

  vga_printstr(glyphptr);

  return vga_tell();    
}

/*
 * vga_printint
 * Prints @src in decimal representation at the current cursor
 * position.
 */
uint16_t *vga_printint(int32_t src) {
  if (src < 0) {
    src *= -1;
    vga_putch('-');
  }

  vga_printuint(src);
  
  return vga_tell();
}

/*
 * vga_printptr
 * Prints the address @src is pointing to.
 */
uint16_t *vga_printptr(void *ptr) {
  uint32_t ptraddr = (uint32_t)ptr;
  return vga_printhex(ptraddr);
}
