#if defined(__linux__)
#  error "This program needs to be build with a cross compiler"
#endif

#if !defined(__i386__)
#  error "You have to use a ix86-elf compiler!"
#endif

#include <stddef.h>
#include <stdint.h>

#include "include/vga.h"


void kernel_main(void) {
  char *str = "This is just a simple test.\0";

  for (int i = 0; str[i]; i++)
    putc(10 + i * 12, 10, str[i], 0xffffff);
}
