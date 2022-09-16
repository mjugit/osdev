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

  fact(!kmemcmp(&expected, &actual, sizeof(vga_config)));
}

deftest(vga_reset_always_resets_backbuffer) {
  uint16_t expected[ROWS * COLS];
  kmemset16(expected, 0x00, ROWS * COLS);
  kmemset16(backbuffer, 0xff, ROWS * COLS);

  uint16_t *cursor_ptr = vga_reset();

  fact(!kmemcmp(expected, backbuffer, sizeof expected));
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

deftest(vga_putch_reaches_screenbounds_resets_cursor) {
  size_t total_chars = COLS * ROWS;

  uint16_t *cursor_start = vga_reset();
  fact(cursor_start == backbuffer);

  for (size_t index = 0; index < total_chars; index++)
    vga_putch('.');

  uint16_t *cursor_end = vga_tell();
  fact (cursor_end == cursor_start)
  
}

deftest(vga_setcursor_always_sets_cursor_to_coordinates) {
  vga_reset();

  int expectedx = 42;
  int expectedy = 19;
  int indexend  = COLS * expectedy + expectedx;
  for (int col = 0; col < indexend; col++)
    vga_putch(0);

  uint16_t *expected = vga_tell();

  vga_reset();
  uint16_t *actual = vga_setcursor(expectedx, expectedy);

  fact(actual == expected);
}

deftest(vga_refresh_always_synchronizes_frontbuffer_with_backbuffer) {
  vga_reset();
  
  for (size_t index = 0; index < ROWS * COLS; index++)
    vga_putch(0xff);

  vga_refresh();

  fact(!kmemcmp(frontbuffer, backbuffer, sizeof(frontbuffer)));
}

deftest(vga_rotup_always_rotates_screen_and_sets_cursor_to_free_space) { 
  uint16_t expectedempty[3 * COLS];
  kmemset16(expectedempty, 0, 3 * COLS);
  
  size_t rowsup = 3;
  kmemset16(backbuffer, 0xaaaa, rowsup * COLS);
  kmemset16(&backbuffer[rowsup * COLS], 0xffff, (ROWS - rowsup) * COLS);
  vga_refresh();
  uint16_t *freearea = vga_rotup(rowsup);
  
  fact(!kmemcmp(expectedempty, freearea, sizeof(expectedempty)));
  fact(!kmemcmp(backbuffer, &frontbuffer[rowsup * COLS], ((ROWS - rowsup) * COLS * sizeof(uint16_t))));
}


deffixture(vga_test) {
  runtest(vga_configure_always_sets_video_options);
  runtest(vga_reset_always_resets_backbuffer);
  runtest(vga_setattr_always_sets_default_attributes);
  runtest(vga_putch_always_puts_char_and_moves_cursor);
  runtest(vga_putch_reaches_screenbounds_resets_cursor);
  runtest(vga_setcursor_always_sets_cursor_to_coordinates);
  runtest(vga_refresh_always_synchronizes_frontbuffer_with_backbuffer);
  runtest(vga_rotup_always_rotates_screen_and_sets_cursor_to_free_space);
}

int main(void) {
  runfixture(vga_test);
  report();
}
