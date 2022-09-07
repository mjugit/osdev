#if defined(__linux__)
#  error "This program needs to be build with a cross compiler"
#endif

#if !defined(__i386__)
#  error "You have to use a ix86-elf compiler!"
#endif

#include <stddef.h>
#include <stdint.h>

#include "libc/include/string.h"
#include "libk/include/vga.h"

void kmain(void) {
  tui_initialize();

  tui_printf("value: %x", 0xabcdef12345);
  tui_refresh();
}
