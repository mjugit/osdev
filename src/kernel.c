#include <stdint.h>
#include <stddef.h>


#if defined(__linux__)
#  error "This program needs to be build with a cross compiler"
#endif

#if !defined(__i386__)
#  error "You have to use a ix86-elf compiler!"
#endif



#include "console-font.h"
#include "include/string.h"


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define FRAMEBUFFER_LOCATION 0xa0000

void write_string(int x, int y, const char *str);
void kernel_main(void);

void set_pixel(int pos_x, int pos_y, uint32_t color) {
  void* location = (void*)(FRAMEBUFFER_LOCATION) + (SCREEN_WIDTH * pos_y * sizeof(color)) + (pos_x * sizeof(color));
  memset32(location, color, 1);
}

void putc(int pos_x, int pos_y, char ch, uint32_t color) {
  const int FONT_HEIGHT = 16;
  const int FONT_WIDTH = 12;
  const int FONT_BITS_PER_ROW = 16;
  uint16_t char_bitmap[FONT_HEIGHT];
  
  memcpy(&char_bitmap, FONT_12X16 + ch * 16, sizeof(uint16_t) * 16);
  
  for (int ch_row = 0; ch_row < FONT_HEIGHT; ch_row++) {
    uint16_t row_bitmap = char_bitmap[ch_row] >> FONT_BITS_PER_ROW - FONT_WIDTH;

    for (int ch_col = 11; ch_col >= 0; ch_col--) {
      if (row_bitmap & 1)
	set_pixel(pos_x + ch_col, pos_y + ch_row, color);
      row_bitmap = row_bitmap >> 1;
    }
  }
}

void write_string(int x, int y, const char *str) {
    for (int i = 0; str[i]; i++)
      putc(x + i * 12, y, str[i], 0xaa3939);
}


void kernel_main(void) {
  char *str = "This is just a simple test.\0";
  write_string(10, 10, str);
}
