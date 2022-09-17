#include "include/kstd.h"

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
void kprintf(char *format, ...) {
  char *formatptr = format;

  va_list args;
  va_start(args, format);
  
  while (*formatptr) {
    if (*formatptr == '%') {
      formatptr++;

      uint64_t uint_repl;
      
      switch (*formatptr) {

      case 'x':
	uint_repl = va_arg(args, uint64_t);
	vga_printhex(uint_repl);
	break;

      case 'u':
	uint_repl = va_arg(args, uint64_t);
	vga_printuint(uint_repl);
	break;

      default:
	vga_putch('%');
	break;
      }
      
    } else {
      vga_putch(*formatptr);
    }
    
    formatptr++;
  }
  
  va_end(args);
}
