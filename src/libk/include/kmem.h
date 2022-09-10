#ifndef KMEM_H
#  define KMEM_H

#include <stdint.h>
#include <stddef.h>

/*
 * kmemcpy
 * Copies @count bytes from @src to @dst.
 */
extern void* kmemcpy(void *dest, const void *src, size_t count);

/*
 * kmemcmp
 * Compares @count bytes of @area1 and @area2.
 */
extern int kmemcmp(const void *area1, const void *area2, size_t count);

/*
 * kmemset
 * Sets @count bytes of @dest to @src.
 */
extern void* kmemset(void *dest, int src, size_t count);

/*
 * kmemset8
 * Sets @count 8 bit blocks of @dest to @src.
 */
extern void* kmemset8(uint8_t *dest, uint8_t src, size_t count);

/*
 * kmemset16
 * Sets @count 16 bit blocks of @dest to @src.
 */
extern void* kmemset16(uint16_t *dest, uint16_t src, size_t count);

/*
 * kmemset32
 * Sets @count 32 bit blocks of @dest to @src.
 */
extern void* kmemset32(uint32_t *dest, uint32_t src, size_t count);

/*
 * kmemset64
 * Sets @count 64 bit blocks of @dest to @src.
 */
extern void* kmemset64(uint64_t *dest, uint64_t src, size_t count);

#endif
