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

  uint64_t value = 0x12345abcdef;
  tui_printf("As hex: %x", value);
  tui_writeline("");
  tui_printf("As uint: %u", value);
  tui_refresh();
}
