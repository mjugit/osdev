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

  for (size_t i = 0; i < 10; i++) {
    char *nextstr = ((i % 2) == 1)
      ? "<<<<< String 1"
      : ">>>>> String 2";
      
    for (size_t j = 0; j < 3; j++) {
      tui_writeline(nextstr);
    }
  }
  
  tui_refresh();
}
