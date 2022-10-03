#include "../include/utest.h"
#include "../../libk/include/kstd.h"
#include "../../libk/include/vga.h"

#define ROWS 25
#define COLS 80

static uint16_t backbuffer[COLS * ROWS];
static uint16_t frontbuffer[COLS * ROWS];


deftest(kprintf__formats_hex_output) {
  const char *expectedstr = "Test 0x1234\0";
  uint16_t *expectedptr = vga_tell();
  vga_printstr(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %x\0", 0x1234);

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__formats_uint_output) {
  const char *expectedstr = "Test 1234\0";
  uint16_t *expectedptr = vga_tell();
  vga_printstr(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %u\0", 1234);

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__formats_int_output) {
  const char *expectedstr = "Test -1234\0";
  uint16_t *expectedptr = vga_tell();
  vga_printstr(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %d\0", -1234);

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__formats_string_output) {
  const char *expectedstr = "Test abcdef\0";
  uint16_t *expectedptr = vga_tell();
  vga_printstr(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %s\0", "abcdef");

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__formats_single_char_output) {
  const char *expectedstr = "Test c\0";
  uint16_t *expectedptr = vga_tell();
  vga_printstr(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %c\0", 'c');

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__puts_percent) {
  const char *expectedstr = "Test %\0";
  uint16_t *expectedptr = vga_tell();
  vga_printstr(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %\0");

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}


deffixture(kernel_output) {
  runtest(kprintf__formats_hex_output);
  runtest(kprintf__formats_uint_output);
  runtest(kprintf__formats_int_output);
  runtest(kprintf__formats_string_output);
  runtest(kprintf__formats_single_char_output);
  runtest(kprintf__puts_percent);
}



void setup_graphics(void) {
  vga_configure(frontbuffer, backbuffer, COLS, ROWS, TABLEN);
  vga_reset();
}


int main(void) {
  setupfn(setup_graphics);
  runfixture(kernel_output);
  report();

  return 0;
}

