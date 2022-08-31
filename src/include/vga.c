#include "vga.h"

static void __plot_pixel(size_t posx, size_t posy, color_t color) {
  memset((void*)FBUFF + (RESX * posy * 4 + (posx * 4)), color, 4);
}

void putc(size_t posx, size_t posy, char ch, color_t color) {
  const int FHEIGHT = 16;
  const int FWIDTH = 12;
  const int FBITS = 16;
  
  uint16_t bitmap[16];
  memcpy(&bitmap, FONT_12x16 + ch * 16, 32);
  
  for (int chy = 0; chy < FHEIGHT; chy++) {
    uint16_t row = bitmap[chy] >> (FBITS - FWIDTH);

    for (int chx = 11; chx >= 0; chx--) {
      if (row & 1)
	__plot_pixel(posx + chx, posy + chy, color);
      row = row >> 1;
    }
  }
}

void fill_area(size_t posx, size_t posy, size_t sizex, size_t sizey, color_t color) {
  for (size_t rowi = 0; rowi < sizey; rowi++) {
    for (size_t coli = 0; coli < sizex; coli++) {
       __plot_pixel(posx + coli, posy + rowi, color);
    }
  }
}
