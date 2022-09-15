#include "include/vga.h"

static size_t _cursor_x;
static size_t _cursor_y;

// Attributes for the next char
static vga_attribute _attributes;

// Backbuffer for double buffering
static vga_char _backbuffer[TUI_CELLS * TUI_ROWS];


void tui_initialize(void) {
  _cursor_x = 0;
  _cursor_y = 0;

  _attributes = vgacolor(VGA_LIGHT_GREY, VGA_BLACK);
}


void tui_putch(char ch) {
  size_t cell_index = _cursor_y * TUI_CELLS + _cursor_x;
  _backbuffer[cell_index] = vgachar(ch, _attributes);

  if (++_cursor_x == TUI_CELLS) {
    _cursor_x = 0;
    _cursor_y++;
  }

  if (_cursor_y > TUI_ROWS)
    tui_scrollup();
}

void tui_write(const char *str) {
  while (*str)
    tui_putch(*str++);
}

void tui_writeline(const char *str) {
  _cursor_x = 0;
  tui_write(str);
  _cursor_x = 0;

  if (++_cursor_y > TUI_ROWS)
    tui_scrollup();
}

void tui_refresh(void) {
  memcpy((void*)FRONTBUFFER_ADDR, _backbuffer, sizeof(_backbuffer));
}

void tui_clear(void) {
  vga_char background = vgachar(' ', _attributes);
  memset16(_backbuffer, background, TUI_CELLS * TUI_ROWS);
  _cursor_x = 0;
  _cursor_y = 0;
  
  tui_refresh();
}

void tui_scrollup(void) {
  vga_char *secondrow = _backbuffer + TUI_CELLS;
  size_t bytes_to_move = sizeof(_backbuffer) - TUI_CELLS * sizeof(vga_char);
  
  memcpy(_backbuffer, secondrow, bytes_to_move);
  _cursor_x = 0;
  _cursor_y = TUI_ROWS;
}


static size_t _hex_to_string(char *buffer, size_t position, uint64_t value) {
  char replacement_buffer[25];
  char symbols[16] = "0123456789abcdef";
  size_t size = 0;

  do {
    replacement_buffer[size++] = symbols[value % 16];
    value /= 16;
  } while (value != 0);

  replacement_buffer[size++] = 'x';
  replacement_buffer[size++] = '0';
  
  for (int buff_index = size - 1; buff_index >= 0; buff_index--)
    buffer[position++] = replacement_buffer[buff_index];

  return size + 1;
}

static size_t _uint_to_string(char *buffer, int position, uint64_t value) {
  char replacement_buffer[25];
  char symbols[10] = "0123456789";
  size_t size = 0;

  do {
    replacement_buffer[size++] = symbols[value % 10];
    value /= 10;
  } while (value != 0);

  for (int buff_index = size - 1; buff_index >= 0; buff_index--)
    buffer[position++] = replacement_buffer[buff_index];

  return size + 1;
}

void tui_printf(char *format, ...) {
  char textbuffer[1024];
  size_t buffer_size = 0;
  uint64_t replacement_buffer = 0;

  va_list args;
  va_start(args, format);

  for (size_t format_index = 0; format[format_index]; format_index++) {
    if (format[format_index] == '%') {

      switch (format[++format_index]) {
      case 'x':
	replacement_buffer = va_arg(args, uint64_t);
	buffer_size += _hex_to_string(textbuffer, buffer_size, (uint64_t)replacement_buffer);
	break;

      case 'u':
	replacement_buffer = va_arg(args, uint64_t);
	buffer_size += _uint_to_string(textbuffer, buffer_size, (uint64_t)replacement_buffer);
	break;
	
      default:
	textbuffer[buffer_size++] = '%';
	break;
      }
      
    } else {
      textbuffer[buffer_size++] = format[format_index];
    }
  }  
  va_end(args);

  textbuffer[++buffer_size] = '\0';
  tui_write(textbuffer);
}
