#include "../include/utest.h"
#include "../../libk/include/vga.h"
#include "../../libk/include/kmem.h"

#define ROWS 25
#define COLS 80

static uint16_t backbuffer[COLS * ROWS];
static uint16_t frontbuffer[COLS * ROWS];

deftest(vga_configure__sets_video_options) {
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

deftest(vga_reset__clears_backbuffer) {
  uint16_t expected[ROWS * COLS];
  kmemset16(expected, 0x00, ROWS * COLS);
  kmemset16(backbuffer, 0xff, ROWS * COLS);

  uint16_t *cursor_ptr = vga_reset();

  fact(!kmemcmp(expected, backbuffer, sizeof expected));
  fact(cursor_ptr == backbuffer);
}

deftest(vga_setattr__sets_attr_of_next_chars) {
  uint8_t expected = 0xff;

  uint8_t actual = vga_setattr(expected);

  fact(actual == expected);
}

deftest(vga_putch__puts_char_at_cursor) {
  uint16_t *startpos = vga_tell();
  uint8_t expected_attr = vga_attr(VGA_WHITE, VGA_BLACK);
  char expected_ch = 'x';
  
  vga_setattr(expected_attr);
  uint16_t *updatedpos = vga_putch(expected_ch);

  fact(updatedpos > startpos);
  fact(*startpos == vga_ch(expected_ch, expected_attr));
}

deftest(vga_putch__scrolls_if_screen_is_full) {
  vga_reset();
  size_t total_chars = COLS * ROWS;

  for (size_t index = 0; index < total_chars; index++)
    vga_putch('.');

  uint16_t *cursor_end = vga_tell();
  uint16_t *cursor_expected = vga_setcursor(0, ROWS - 1);
  fact (cursor_end == cursor_expected);
}

deftest(vga_setcursor__moves_cursor) {
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

deftest(vga_refresh__copies_backbuffer_to_frontbuffer) {
  vga_reset();
  
  for (size_t index = 0; index < ROWS * COLS; index++)
    vga_putch(0xff);

  vga_refresh();

  fact(!kmemcmp(frontbuffer, backbuffer, sizeof(frontbuffer)));
}

deftest(vga_rotup__scrolls_screen_up) { 
  uint16_t expectedempty[3 * COLS];
  kmemset16(expectedempty, 0, 3 * COLS);
  
  size_t rowsup = 3;
  kmemset16(backbuffer, 0xaaaa, rowsup * COLS);
  kmemset16(&backbuffer[rowsup * COLS], 0xffff, (ROWS - rowsup) * COLS);
  vga_refresh();
  uint16_t *freearea = vga_rotup(rowsup);
  
  fact(!kmemcmp(expectedempty, freearea, sizeof(expectedempty)));
  fact(!kmemcmp(backbuffer, &frontbuffer[rowsup * COLS], ((ROWS - rowsup) * COLS * sizeof(uint16_t))));
  fact(freearea == vga_tell());
}

deftest(vga_print__prints_null_terminated_string) {
  const char *dummystr = "Hello, world!\0";
  const uint8_t attr = vga_attr(VGA_WHITE, VGA_BLACK);

  uint16_t expected[sizeof(dummystr) * sizeof(uint16_t)];

  for (size_t strindex = 0; dummystr[strindex]; strindex++)
    expected[strindex] = vga_ch(dummystr[strindex], attr);
  
  vga_reset();

  vga_print(dummystr);

  fact(!kmemcmp(backbuffer, expected, sizeof(expected)));
}

deftest(vga_newline__performs_linefeed) {
  vga_reset();
  vga_setcursor(10, 0);
  vga_newline();

  fact(vga_getcol() == 0);
  fact(vga_getrow() == 1);
}


deffixture(vga_test) {
  runtest(vga_configure__sets_video_options);
  runtest(vga_reset__clears_backbuffer);
  runtest(vga_setattr__sets_attr_of_next_chars);
  runtest(vga_putch__puts_char_at_cursor);
  runtest(vga_putch__scrolls_if_screen_is_full);
  runtest(vga_setcursor__moves_cursor);
  runtest(vga_refresh__copies_backbuffer_to_frontbuffer);
  runtest(vga_rotup__scrolls_screen_up);
  runtest(vga_print__prints_null_terminated_string);
  runtest(vga_newline__performs_linefeed);
}

int main(void) {
  runfixture(vga_test);
  report();
}
