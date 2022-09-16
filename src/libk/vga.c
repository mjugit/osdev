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
			  size_t rows) {
  _config = (vga_config) {
    .frontbuff = frontbuff_ptr,
    .backbuff = backbuff_ptr,
    .sizex = cols,
    .sizey = rows
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
  *cursor = vga_ch(ch, _defaultattr);

  if (++_cursorx >= _config.sizex) {
    ++_cursory;
    _cursorx = 0;

    if (_cursory >= _config.sizey)
      vga_rotup(1);
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
  vga_setcursor(0, 0);

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
uint16_t *vga_print(const char *str) {
  while (*str)
    vga_putch(*str++);

  return vga_tell();
}
