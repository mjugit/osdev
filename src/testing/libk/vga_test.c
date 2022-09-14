#include "../include/utest.h"
#include "../../libk/include/vga.h"
#include "../../libk/include/kmem.h"

#define ROWS 25
#define COLS 80

static uint16_t backbuffer[COLS * ROWS];
static uint16_t frontbuffer[COLS * ROWS];

deftest(vga_initialize_always_configures_video) {
  uint16_t dummybuff[64];
  
  vga_config expected = {
    .frontbuff = dummybuff,
    .backbuff = dummybuff,
    .sizex = 97,
    .sizey = 123
  };

  vga_config actual = vga_initialize(expected.frontbuff,
				     expected.backbuff,
				     expected.sizex,
				     expected.sizey);

  fact(kmemcmp(&expected, &actual, sizeof(vga_config)) == 0);
}

deftest(vga_reset_always_resets_backbuffer) {
  uint16_t expected[ROWS * COLS];
  kmemset16(expected, 0x00, ROWS * COLS);
  kmemset16(backbuffer, 0xff, ROWS * COLS);

  vga_reset();

  fact(kmemcmp(expected, backbuffer, sizeof expected) == 0);
}


deffixture(vga_test) {
  runtest(vga_initialize_always_configures_video);
  runtest(vga_reset_always_resets_backbuffer);
}


void setup_testenv(void) {
  
}

int main(void) {
  runfixture(vga_test);
  report();
}
