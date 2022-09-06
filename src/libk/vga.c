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
}


void tui_writeline(const char *str) {
  while (*str)
    tui_putch(*str++);

  _cursor_x = 0;
  _cursor_y++;
}

void tui_refresh(void) {
  memcpy((void*)FRONTBUFFER_ADDR, _backbuffer, sizeof(_backbuffer));
}
