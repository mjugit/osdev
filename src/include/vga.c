#include "vga.h"

/* static void __plot_pixel(size_t posx, size_t posy, color_t color) { */
/*   memset((void*)FBUFF + (RESX * posy * 4 + (posx * 4)), color, 4); */
/* } */

/* void putc(size_t posx, size_t posy, char ch, color_t color) { */
/*   const int FHEIGHT = 16; */
/*   const int FWIDTH = 12; */
/*   const int FBITS = 16; */
  
/*   uint16_t bitmap[16]; */
/*   memcpy(&bitmap, FONT_12x16 + ch * 16, 32); */
  
/*   for (int chy = 0; chy < FHEIGHT; chy++) { */
/*     uint16_t row = bitmap[chy] >> (FBITS - FWIDTH); */

/*     for (int chx = 11; chx >= 0; chx--) { */
/*       if (row & 1) */
/* 	__plot_pixel(posx + chx, posy + chy, color); */
/*       row = row >> 1; */
/*     } */
/*   } */
/* } */

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
