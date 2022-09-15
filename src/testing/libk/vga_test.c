#include "../include/utest.h"
#include "../../libk/include/vga.h"
#include "../../libk/include/kmem.h"

#define ROWS 25
#define COLS 80

static uint16_t backbuffer[COLS * ROWS];
static uint16_t frontbuffer[COLS * ROWS];

deftest(vga_configure_always_sets_video_options) {
  vga_config expected = {
    .frontbuff = frontbuffer,
    .backbuff = backbuffer,
    .sizex = COLS,
    .sizey = ROWS
  };

  vga_config actual = vga_configure(expected.frontbuff,
				     expected.backbuff,
				     expected.sizex,
				     expected.sizey);

  fact(kmemcmp(&expected, &actual, sizeof(vga_config)) == 0);
}

deftest(vga_reset_always_resets_backbuffer) {
  uint16_t expected[ROWS * COLS];
  kmemset16(expected, 0x00, ROWS * COLS);
  kmemset16(backbuffer, 0xff, ROWS * COLS);

  uint16_t *cursor_ptr = vga_reset();

  fact(kmemcmp(expected, backbuffer, sizeof expected) == 0);
  fact(cursor_ptr == backbuffer);
}

deftest(vga_setattr_always_sets_default_attributes) {
  uint8_t expected = 0xff;

  uint8_t actual = vga_setattr(expected);

  fact(actual == expected);
}

deftest(vga_putch_always_puts_char_and_moves_cursor) {
  uint16_t *startpos = vga_tell();
  uint8_t expected_attr = vga_attr(VGA_WHITE, VGA_BLACK);
  char expected_ch = 'x';
  
  vga_setattr(expected_attr);
  uint16_t *updatedpos = vga_putch(expected_ch);

  fact(updatedpos > startpos);
  fact(*startpos == vga_ch(expected_ch, expected_attr));
}

deffixture(vga_test) {
  runtest(vga_configure_always_sets_video_options);
  runtest(vga_reset_always_resets_backbuffer);
  runtest(vga_setattr_always_sets_default_attributes);
  runtest(vga_putch_always_puts_char_and_moves_cursor);
}

int main(void) {
  runfixture(vga_test);
  report();
}
