#include "../include/utest.h"
#include "../../libk/include/kstd.h"
#include "../../libk/include/vga.h"

#define ROWS 25
#define COLS 80

static uint16_t backbuffer[COLS * ROWS];
static uint16_t frontbuffer[COLS * ROWS];


deftest(kprintf__formats_hex_ouput) {
  const char *expectedstr = "Test 0x1234\0";
  uint16_t *expectedptr = vga_tell();
  vga_print(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %x\0", 0x1234);

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__formats_uint_ouput) {
  const char *expectedstr = "Test 1234\0";
  uint16_t *expectedptr = vga_tell();
  vga_print(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %u\0", 1234);

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}

deftest(kprintf__puts_percent) {
  // TODO: DOES NOT WORK!
  const char *expectedstr = "Test %\0";
  uint16_t *expectedptr = vga_tell();
  vga_print(expectedstr);
  uint16_t *actualptr = vga_setcursor(0, 1);

  kprintf("Test %\0");

  fact(!kmemcmp(expectedptr, actualptr, sizeof(expectedstr) * sizeof(uint16_t)));
}


deffixture(kernel_output) {
  runtest(kprintf__formats_hex_ouput);
  runtest(kprintf__formats_uint_ouput);
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

