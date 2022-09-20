#include "include/kstd.h"

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
 * %     percent sign
 */
void kprintf(char *format, ...) {
  char *formatptr = format;

  va_list args;
  va_start(args, format);
  
  while (*formatptr) {
    if (*formatptr == '%') {
      formatptr++;

      uint32_t uint_repl;
      int32_t int_repl;
      char *str_repl;
      
      switch (*formatptr) {

      case 'x':
	uint_repl = va_arg(args, uint32_t);
	vga_printhex(uint_repl);
	break;

      case 'u':
	uint_repl = va_arg(args, uint32_t);
	vga_printuint(uint_repl);
	break;

      case 'd':
	int_repl = va_arg(args, int32_t);
	vga_printint(int_repl);
	break;

      case 's':
	str_repl = va_arg(args, char*);
	vga_printstr(str_repl);
	break;

      case 'c':
	int_repl = va_arg(args, int32_t);
	vga_putch(int_repl);
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
