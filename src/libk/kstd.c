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
 * %%    percent sign
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
      char char_repl;
      
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
	char_repl = va_arg(args, uint32_t);
	vga_putch(char_repl);
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
  vga_refresh();
}

/*
 * kencode_gdt
 * Creates an entry for the global descriptor table at @gdtptr
 * containing the @base address, the @limit, the as well as the given
 * @accessbyte and @flags.
 */
void kencode_gdt(uint8_t *dest, struct gdt_entry src) {
  *dest++ = src.limit & 0xff;
  *dest++ = (src.limit >> 8) & 0xff;
  
  *dest++ = src.base & 0xff;
  *dest++ = (src.base >> 8) & 0xff;
  *dest++ = (src.base >> 16) & 0xff;
  *dest++ = src.accessbyte;
  *dest++ = (src.flags << 4);
  *dest   = (src.base >> 24) & 0xff;
}

struct gdt_entry kdecode_gdt(uint8_t *src) {
  struct gdt_entry result;

  result.limit = (uint16_t) *src;
  src += 2;

  result.base = (uint16_t) *src;
  src += 2;
  result.base |= ((uint8_t)(*src) << 16);
  src++;

  result.accessbyte = (uint8_t) *src;
  src++;

  result.limit = (uint8_t) *src & 0x0f;
  result.flags = (uint8_t) *src & 0xf0;

  result.base = ((uint8_t)(*src) << 24);
  
  return result;
}
