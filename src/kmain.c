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

#include "libk/include/kmem.h"
#include "libk/include/vga.h"

static uint16_t _backbuff[VGA_COLS * VGA_ROWS];
static uint16_t *_frontbuff = (uint16_t*)VGA_FRONTBUFF;

void kmain(void) {
  vga_configure(_frontbuff, _backbuff, VGA_COLS, VGA_ROWS);
  vga_reset();

  vga_setattr(vga_attr(VGA_WHITE, VGA_BLACK));
  vga_print("Hello, world!");
  vga_refresh();
}
