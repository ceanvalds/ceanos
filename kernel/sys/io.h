#ifndef __IO__
#define __IO__

#include <stdint.h>

volatile uint8_t inb(uint16_t port);
volatile void outb(uint16_t port, uint8_t data);
volatile uint16_t inw(uint16_t port);
volatile void outl(uint16_t port, uint32_t data); 
void outw(unsigned short port, unsigned short value);
void insl(uint16_t port, void* addr, int count);

#endif
