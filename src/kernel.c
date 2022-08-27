#include <stdint.h>
#include <stddef.h>

#if defined(__linux__)
#  error "This program needs to be build with a cross compiler"
#endif

#if !defined(__i386__)
#  error "You have to use a ix86-elf compiler!"
#endif

#define SCREEN_BUFFER 0xB8000
#define SCREEN_COLS 80
#define SCREEN_ROWS 25

// MACROS
#define colorpair(fg,bg) ((fg) | ((bg) << 4))
// Inline 
#define ch(ch, attr) ((ch) | ((attr) << 8))
// Get the linear offset realive to the start of the video buffer
#define cursor(col, row) ((col) + ((row) * (SCREEN_COLS)))
#define strlen(src, len) (for (len = 0; src[len]; len++)) 

typedef enum {
  VGA_BLACK	    = 0,
  VGA_BLUE	    = 1,
  VGA_GREEN	    = 2,
  VGA_CYAN	    = 3,
  VGA_RED	    = 4,
  VGA_MAGENTA	    = 5,
  VGA_BROWN	    = 6,
  VGA_LIGHT_GREY    = 7,
  VGA_DARK_GREY	    = 8,
  VGA_LIGHT_BLUE    = 9,
  VGA_LIGHT_GREEN   = 10,
  VGA_LIGHT_CYAN    = 11,
  VGA_LIGHT_RED	    = 12,
  VGA_LIGHT_MAGENTA = 13,
  VGA_LIGHT_BROWN   = 14,
  VGA_WHITE	    = 15
} color;

typedef uint16_t ch_t;
typedef uint8_t ch_attr_t;


static ch_t *_screen_buffer;
static ch_attr_t _theme;


void memcpy(void *dst, void *src, size_t count);
void memset(void *dst, void *src, size_t size, size_t count);
void tui_init(size_t cols, size_t rows);
void tui_write_at(size_t col, size_t row, char *text);

void kernel_main(void);

void memcpy(void *dst, void *src, size_t count) {
  for (size_t offset = 0; offset < count; offset++)
    *(uint8_t*)(dst + offset) = *(uint8_t*)(src + offset);
}

void memset(void *dst, void *src, size_t size, size_t count) {
  for (size_t offset = 0; offset < count; offset++)
    memcpy(dst + offset * size, src, size);
}


void tui_init(size_t cols, size_t rows) {
  _theme = colorpair(VGA_CYAN, VGA_BLUE);
  ch_t background = ch(' ', _theme);

  memset(_screen_buffer, &background, sizeof(ch_t), cols * rows);
}

void tui_write_at(size_t col, size_t row, char *text) {
  size_t pos = cursor(col, row);
  
  for (size_t len = 0; text[len]; (len++), (pos++)) {
    ch_t next_char = ch(text[len], _theme);
    memset(_screen_buffer + pos, &next_char, sizeof(ch_t), 1);
    pos++;
  }
}



void kernel_main(void) {
  _screen_buffer = (ch_t*)SCREEN_BUFFER;
  tui_init(SCREEN_COLS, SCREEN_ROWS);
  tui_write_at(5, 0, "X (5, 0)\0");
  tui_write_at(2, 3, "X (2, 3)\0");
  tui_write_at(8, 10, "X (8, 10)\0");
}
