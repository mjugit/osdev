#include "../include/utest.h"
#include "../../libk/include/vga.h"
#include "../../libk/include/kmem.h"

#define ROWS 25
#define COLS 80

static uint16_t backbuffer[COLS * ROWS];
static uint16_t frontbuffer[COLS * ROWS];


// Configuration functions

deftest(vga_configure__sets_video_options) {
  vga_config valuestr = {
    .frontbuff = frontbuffer,
    .backbuff = backbuffer,
    .sizex = COLS,
    .sizey = ROWS,
    .tablen = TABLEN
  };

  vga_config actual = vga_configure(valuestr.frontbuff,
				    valuestr.backbuff,
				    valuestr.sizex,
				    valuestr.sizey,
				    valuestr.tablen);

  fact(!kmemcmp(&valuestr, &actual, sizeof(vga_config)));
}


deftest(vga_reset__clears_backbuffer) {
  uint16_t valuestr[ROWS * COLS];
  kmemset16(valuestr, 0x00, ROWS * COLS);
  kmemset16(backbuffer, 0xff, ROWS * COLS);

  uint16_t *cursor_ptr = vga_reset();

  fact(!kmemcmp(valuestr, backbuffer, sizeof valuestr));
  fact(cursor_ptr == backbuffer);
}


deftest(vga_setattr__sets_attr_of_next_chars) {
  uint8_t valuestr = 0xff;

  uint8_t actual = vga_setattr(valuestr);

  fact(actual == valuestr);
}


deffixture(config_functions) {
  runtest(vga_configure__sets_video_options);
  runtest(vga_reset__clears_backbuffer);
  runtest(vga_setattr__sets_attr_of_next_chars);
}



// Display essentials

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

  uint16_t *valuestr = vga_tell();

  vga_reset();
  uint16_t *actual = vga_setcursor(expectedx, expectedy);

  fact(actual == valuestr);
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


deffixture(display_essentials) {
  runtest(vga_putch__puts_char_at_cursor);
  runtest(vga_putch__scrolls_if_screen_is_full);
  runtest(vga_setcursor__moves_cursor);
  runtest(vga_refresh__copies_backbuffer_to_frontbuffer);
  runtest(vga_rotup__scrolls_screen_up);
}



// Components of the printf function
  
deftest(vga_printstr__prints_null_terminated_string) {
  const char *dummystr = "Hello, world!\0";
  const uint8_t attr = vga_attr(VGA_WHITE, VGA_BLACK);

  uint16_t valuestr[sizeof(dummystr) * sizeof(uint16_t)];

  for (size_t strindex = 0; dummystr[strindex]; strindex++)
    valuestr[strindex] = vga_ch(dummystr[strindex], attr);
  
  vga_reset();

  vga_printstr(dummystr);

  fact(!kmemcmp(backbuffer, valuestr, sizeof(valuestr)));
}


deftest(vga_newline__performs_linefeed) {
  vga_reset();
  vga_setcursor(10, 0);
  vga_newline();

  fact(vga_getcol() == 0);
  fact(vga_getrow() == 1);
}


deftest(vga_tab__moves_cursor_to_next_tabstop) {
  vga_reset();
  
  uint16_t *cursorbefore = vga_setcursor(4, 0);
  uint16_t *cursorafter = vga_tab();

  fact(cursorafter > cursorbefore);
  fact(vga_getcol() == TABLEN - 1);

  size_t somewhere = TABLEN * 3 - TABLEN / 3;
  cursorbefore = vga_setcursor(somewhere, 0);
  cursorafter = vga_tab();

  fact(cursorafter > cursorbefore);
  fact(cursorafter == vga_setcursor(TABLEN * 3 - 1, 0));

  size_t edge = COLS - 2;
  vga_setcursor(edge, 0);
  size_t _cursorybefore = vga_getrow();
  vga_tab();

  fact(_cursorybefore < vga_getrow());
}


deftest(vga_printhex__prints_src_as_hex) {
  uint64_t valuelong = 0x12345;
  const char *valuestr = "0x12345\0";
  
  uint16_t *expectedpos = vga_reset();
  vga_printstr(valuestr);
  uint16_t *actualpos = vga_newline();
  vga_printhex(valuelong);

  size_t valuestrlen = 0;
  while (valuestr[valuestrlen++]);

  fact(!kmemcmp(expectedpos, actualpos, valuestrlen * sizeof(uint16_t)));
}


deftest(vga_printuint__prints_src_as_unsigned_decimal) {
  uint64_t valuelong = 1234;
  const char *valuestr = "1234\0";

  uint16_t *expectedpos = vga_reset();
  vga_printstr(valuestr);
  uint16_t *actualpos = vga_newline();
  vga_printuint(valuelong);

  size_t valuestrlen = 0;
  while (valuestr[valuestrlen++]);

  fact(!kmemcmp(expectedpos, actualpos, valuestrlen * sizeof(uint16_t)));
}


deftest(vga_printint__prints_src_as_decimal) {
  uint64_t valuelong = -1234;
  const char *valuestr = "-1234\0";

  uint16_t *expectedpos = vga_reset();
  vga_printstr(valuestr);
  uint16_t *actualpos = vga_newline();
  vga_printint(valuelong);

  size_t valuestrlen = 0;
  while (valuestr[valuestrlen++]);

  fact(!kmemcmp(expectedpos, actualpos, valuestrlen * sizeof(uint16_t)));
}


deftest(vga_printptr__prints_address_of_ptr) {
  void *valueptr = (void*)0x12345678;
  const char *valuestr = "0x12345678\0";

  uint16_t *expectedpos = vga_reset();
  vga_printstr(valuestr);
  uint16_t *actualpos = vga_newline();
  vga_printptr(valueptr);

  size_t valuestrlen = 0;
  while (valuestr[valuestrlen++]);

  fact(!kmemcmp(expectedpos, actualpos, valuestrlen * sizeof(uint16_t)));
}


deffixture(printf_components) {
  runtest(vga_printstr__prints_null_terminated_string);
  runtest(vga_newline__performs_linefeed);
  runtest(vga_printhex__prints_src_as_hex);
  runtest(vga_printuint__prints_src_as_unsigned_decimal);
  runtest(vga_printint__prints_src_as_decimal);
  runtest(vga_printptr__prints_address_of_ptr);
  runtest(vga_tab__moves_cursor_to_next_tabstop);
}




int main(void) {
  runfixture(config_functions);
  runfixture(display_essentials);
  runfixture(printf_components);
  
  report();
}
