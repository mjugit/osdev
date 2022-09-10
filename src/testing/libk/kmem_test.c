#include "../include/utest.h"
#include "../../libk/include/kmem.h"

static uint8_t testbuffer[200];

deftest(kmemcpy_duplicates_source_at_dest) {
  const uint8_t expected[] = {
    0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
    0x8, 0x9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf
  };

  kmemcpy(testbuffer, expected, sizeof expected);

  for (size_t cmpindex = 0; cmpindex < sizeof(expected); cmpindex++) {
    if (testbuffer[cmpindex] != expected[cmpindex]) {
      fail();
      return;
    }
  }
}


deffixture(kmem_test) {
  runtest(kmemcpy_duplicates_source_at_dest)
}





void setup_testbuffer(void) {
  for (size_t index = 0; index < sizeof testbuffer; index++)
    testbuffer[index] = 0;
}


int main(void) {
  setupfn(&setup_testbuffer);
  runfixture(kmem_test);
  report();
}
