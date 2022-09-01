#if defined(__linux__)
#  error "This program needs to be build with a cross compiler"
#endif

#if !defined(__i386__)
#  error "You have to use a ix86-elf compiler!"
#endif

#include <stddef.h>
#include <stdint.h>

#include "include/vga.h"
#include "include/string.h"


void kernel_main(void) {
  putstring(5, 2, "Works!\0");
  refresh();
}
