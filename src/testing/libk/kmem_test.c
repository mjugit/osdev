#include "../include/utest.h"
#include "../../libk/include/kmem.h"

static uint8_t testbuffer[200];


deftest(kmemcpy_always_copies_src_to_dest) {
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

deftest(kmemcmp_always_compares_two_memory_areas) {
  const uint8_t area1[] = { 0x1, 0x2, 0x3, 0x4, 0x5, 0xa, 0xb, 0xc, 0xd, 0xe };
  const uint8_t area2[] = { 0xa, 0xb, 0xc, 0xd, 0xe, 0x1, 0x2, 0x3, 0x4, 0x5 };

  fact(kmemcmp(area1, area2, sizeof area1) < 0);
  fact(kmemcmp(area2, area1, sizeof area1) > 0);
  fact(kmemcmp(area1, area1, sizeof area1) == 0);
}

deftest(kmemset8_sets_8bitpacket) {
  const uint8_t onetime = 0xff;
  const uint32_t fourtimes = 0xffffffff;

  kmemset8(testbuffer, onetime, 4);

  fact(*(uint32_t*)(testbuffer) == fourtimes);
  fact(testbuffer[4] == 0);
}

deftest(kmemset16_sets_16bitpacket) {
  const uint16_t onetime = 0xffff;
  const uint64_t fourtimes = 0xffffffffffffffff;

  kmemset16((uint16_t*)testbuffer, onetime, 4);

  fact(*(uint64_t*)(testbuffer) == fourtimes);
  fact(testbuffer[8] == 0);
}

deftest(kmemset32_sets_32bitpacket) {
  const uint32_t onetime = 0xffffffff;
  const uint64_t twotimes = 0xffffffffffffffff;

  kmemset32((uint32_t*)testbuffer, onetime, 2);

  fact(*(uint64_t*)testbuffer == twotimes);
  fact(testbuffer[8] == 0);
}

deftest(kmemset64_sets_64bitpacket) {
  const uint64_t onetime = 0xffffffffffffffff;

  kmemset64((uint64_t*)testbuffer, onetime, 2);

  fact(*(uint64_t*)testbuffer == onetime);
  fact(*(uint64_t*)(testbuffer + 1) == onetime);
  fact(testbuffer[16] == 0);
}


deffixture(kmem_test) {
  runtest(kmemcpy_always_copies_src_to_dest);
  runtest(kmemcmp_always_compares_two_memory_areas);
  runtest(kmemset8_sets_8bitpacket);
  runtest(kmemset16_sets_16bitpacket);
  runtest(kmemset32_sets_32bitpacket);
  runtest(kmemset64_sets_64bitpacket);
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
