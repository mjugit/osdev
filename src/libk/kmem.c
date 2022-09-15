#include "include/kmem.h"

/*
 * kmemcpy
 * Copies @count bytes from @src to @dst.
 */
void* kmemcpy(void *dest, const void *src, size_t count) {
  char *tmp = dest;
  const char *s = src;

  while (count--)
    *tmp++ = *s++;
  return dest;
}

/*
 * kmemcmp
 * Compares @count bytes of @area1 and @area2.
 */
int kmemcmp(const void *area1, const void *area2, size_t count) {
  const unsigned char *area1ptr, *area2ptr;
  int cmpresult = 0;

  for (area1ptr = area1, area2ptr = area2; 0 < count; ++area1ptr, ++area2ptr, count--)
    if ((cmpresult = *area1ptr - *area2ptr)) break;
  return cmpresult;
}

/*
 * kmemset
 * Sets @count bytes of @dest to @src.
 */
void* kmemset(void *dest, int src, size_t count) {
  char *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

/*
 * kmemset8
 * Sets @count 8 bit blocks of @dest to @src.
 */
void* kmemset8(uint8_t *dest, uint8_t src, size_t count) {
  uint8_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

/*
 * kmemset16
 * Sets @count 16 bit blocks of @dest to @src.
 */
void* kmemset16(uint16_t *dest, uint16_t src, size_t count) {
  uint16_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

/*
 * kmemset32
 * Sets @count 32 bit blocks of @dest to @src.
 */
void* kmemset32(uint32_t *dest, uint32_t src, size_t count) {
  uint32_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

/*
 * kmemset64
 * Sets @count 64 bit blocks of @dest to @src.
 */
void* kmemset64(uint64_t *dest, uint64_t src, size_t count) {
  uint64_t *area_start = dest;

  while (count--)
    *area_start++ = src;
  return dest;
}

