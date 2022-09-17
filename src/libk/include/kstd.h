#ifndef KSTD_H
#  define KSTD_H

#  include <stdarg.h>
#  include "vga.h"

/*
 * kprintf
 * Writes formated output to the current cursor position. You can use
 * special chars in @format to determine how to represent a value.
 *
 * %x    hexadecimal
 * %u    unsigned decimal
 *
 * %     percent sign
 */
extern void kprintf(char *format, ...);

#endif // KSTD_H
