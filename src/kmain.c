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

  tui_writeline("1 Hello, world!\0");
  tui_writeline("2 Second line!\0");
  tui_writeline("3 Hello, third line!\0");
  tui_scrollup();
  tui_refresh();
}
