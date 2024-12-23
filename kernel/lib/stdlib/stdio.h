#include <stdint.h>

#ifndef __STDIO_H__
#define __SDTIO_H__

void __putc(char c);
void __puts(const char* str);
void __printf(const char* fmt, ...);
int * printf_number(int*, int, bool, int);
void debugf(const char* fmt, ...);

extern void x86_div64_32(uint64_t, uint32_t, uint64_t*, uint32_t*);
extern bool debug_mode;

#define PRINTF_STATE_START 0
#define PRINTF_STATE_LENGTH 1
#define PRINTF_STATE_SHORT 2
#define PRINTF_STATE_LONG 3
#define PRINTF_STATE_SPEC 4
#define PRINTF_STATE_HEX

#define PRINTF_LENGTH_START 0
#define PRINTF_LENGTH_SHORT_SHORT 1
#define PRINTF_LENGTH_SHORT 2
#define PRINTF_LENGTH_LONG 3
#define PRINTF_LENGTH_LONG_LONG 4
#define PRINTF_HEX_LOW 5
#define PRINTF_HEX_UPPER 6

#endif
