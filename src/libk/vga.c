#include "include/vga.h"

static uint16_t _screen[80 * 25];

void putchar(size_t posx, size_t posy, char ch) {
  _screen[posx + posy * CHARS] = vgachar(ch, 7);
}

void refresh(void) {
  memcpy((void*)TBUFF, _screen, sizeof(_screen));
}

void putstring(size_t posx, size_t posy, const char *str) {
  for (size_t charx = 0; str[charx]; charx++)
    putchar(posx + charx, posy, str[charx]);
}

void clear(void) {
  uint16_t bg = 0;
  memset16(_screen, bg, sizeof(_screen));
}
