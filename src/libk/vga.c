#include "include/vga.h"

static vga_config _config;
static uint8_t _defaultattr;
static size_t _cursorx, _cursory;

vga_config vga_initialize(uint16_t *frontbuff_ptr, uint16_t *backbuff_ptr, size_t cols, size_t rows) {
  _config = (vga_config) {
    .frontbuff = frontbuff_ptr,
    .backbuff = backbuff_ptr,
    .sizex = cols,
    .sizey = rows
  };

  return _config;
}

uint16_t *vga_reset(void) {
  kmemset16(_config.backbuff, 0x00, _config.sizex * _config.sizey);
  _cursorx = _cursory = 0;

  return 0; //vga_tell();
}

uint8_t vga_setattr(uint8_t attr) {
  _defaultattr = attr;

  return _defaultattr;
}

uint16_t *vga_tell(void) {
  return &(_config.backbuff[_cursory * _config.sizex + _cursorx]);
}

uint16_t *vga_putch(const char ch) {
  uint16_t *cursor = vga_tell();
  *cursor = vga_ch(ch, 0);

  return vga_tell();
}
