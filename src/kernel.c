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

void scr_init(void);
void scr_write(const char *text);
void kernel_main(void);

enum color {
  COLOR_BLACK = 0,
  COLOR_WHITE = 15
};

static inline uint8_t scr_color(enum color fg, enum color bg) {
  return fg | bg << 4;
}

static inline uint16_t char_entry(unsigned char uc, uint8_t color) {
  return (uint16_t) uc | (uint16_t) color << 8;
}

void scr_init(void) {
  uint8_t color = scr_color(COLOR_BLACK, COLOR_WHITE);

  for (size_t crow = 0; crow < SCREEN_ROWS; crow++) {
    for (size_t ccol = 0; ccol < SCREEN_COLS; ccol++) {
      const size_t index = crow * SCREEN_COLS + ccol;
      ((uint16_t*)SCREEN_BUFFER)[index] = char_entry(' ', color);
    }
  }
}

void scr_write(const char *text) {
  uint8_t color = scr_color(COLOR_BLACK, COLOR_WHITE);
  unsigned int text_len = 0;

  for (; text[text_len]; text_len++);
  for (size_t index = 0; index < text_len; index++)
    ((uint16_t*)SCREEN_BUFFER)[index] = char_entry(text[index], color);
}

void kernel_main(void) {
  scr_init();
  scr_write("Hello, world!\0");
}
