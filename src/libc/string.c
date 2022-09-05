#include "include/string.h"

void* memcpy(void *dest, const void *src, size_t count) {
  char *tmp = dest;
  const char *s = src;

  while (count--)
    *tmp++ = *s++;
  return dest;
}

void* memset(void *dest, int src, size_t count) {
  char *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

void* memset8(uint8_t *dest, uint8_t src, size_t count) {
  uint8_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

void* memset16(uint16_t *dest, uint16_t src, size_t count) {
  uint16_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

void* memset32(uint32_t *dest, uint32_t src, size_t count) {
  uint32_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

void* memset64(uint64_t *dest, uint64_t src, size_t count) {
  uint64_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

