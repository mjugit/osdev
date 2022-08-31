#ifndef __STRING_H__
#  define __STRING_H__

#include <stddef.h>
#include <stdint.h>

extern void memcpy(void *dest, const void *src, size_t count);
extern void memset(void *dest, int src, size_t count);

extern void memset8(uint8_t *dest, uint8_t src, size_t count);
extern void memset16(uint16_t *dest, uint16_t src, size_t count);
extern void memset32(uint32_t *dest, uint32_t src, size_t count);
extern void memset64(uint64_t *dest, uint64_t src, size_t count);


#endif
