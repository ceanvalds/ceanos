#ifndef __cean__
#define __cean__

#include <stdint.h>

#define VERSION "0.04 RC1"
#define new(type) kmalloc(sizeof(type))

extern char *__terry[];
extern const size_t __TERRY_ARRAY_SIZE; 

uint16_t die(const char *die_msg, uint16_t return_value);
void panic(const char *panic);

inline void outw(unsigned short port, unsigned short value);
inline uint16_t inw(unsigned short port);
void insl(uint16_t port, void* addr, int count);

#endif
