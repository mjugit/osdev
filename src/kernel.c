#include <stdint.h>
#include <stddef.h>

#include "console-font.h"

#if defined(__linux__)
#  error "This program needs to be build with a cross compiler"
#endif

#if !defined(__i386__)
#  error "You have to use a ix86-elf compiler!"
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void memcpy(void *dst, void *src, size_t count);
void memset(void *dst, void *src, size_t size, size_t count);
void kernel_main(void);

void memcpy(void *dst, void *src, size_t count) {
  for (size_t offset = 0; offset < count; offset++)
    *(uint8_t*)(dst + offset) = *(uint8_t*)(src + offset);
}

void memset(void *dst, void *src, size_t size, size_t count) {
  for (size_t offset = 0; offset < count; offset++)
    memcpy(dst + offset * size, src, size);
}

void set_pixel(int pos_x, int pos_y, uint32_t color) {
  void* location = (void*)0xA0000 + (SCREEN_WIDTH * pos_y * sizeof(color)) + (pos_x * sizeof(color));
  memset(location, &color, 4, 1);
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

void kernel_main(void) {
  char *str = "This is just a simple test.\0";

  for (int i = 0; str[i]; i++)
    putc(i * 12, 0, str[i], 0xffffffff);
}
