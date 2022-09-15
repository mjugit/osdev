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
  *cursor = vga_ch(ch, 0);

  return vga_tell();
}
