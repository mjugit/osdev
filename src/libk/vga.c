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

void tui_write(const char *str) {
  while (*str)
    tui_putch(*str++);
}

void tui_writeline(const char *str) {
  _cursor_x = 0;
  tui_write(str);
  _cursor_x = 0;
  _cursor_y++;

  if (_cursor_y > TUI_ROWS)
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
