#ifndef KSTD_H
#  define KSTD_H

#  include <stdarg.h>
#  include "vga.h"

struct gdt_entry {
  uint32_t base;
  uint32_t limit;
  uint8_t flags;
  uint8_t accessbyte;
};

/*
 * kprintf
 * Writes formated output to the current cursor position. You can use
 * special chars in @format to determine how to represent a value.
 *
 * %x    hexadecimal
 * %u    unsigned decimal
 * %d    decimal
 * %s    string
 * %c    single char
 *
 * %%    percent sign
 */
extern void kprintf(char *format, ...);

/*
 * kencode_gdt
 * Creates an entry for the global descriptor table at @gdtptr
 * containing the @base address, the @limit, the as well as the given
 * @accessbyte and @flags.
 */
extern void kencode_gdt(uint8_t *dest, struct gdt_entry src);

#endif // KSTD_H
