#include <io.h>
#include <stdint.h>

volatile uint8_t inb(uint16_t port)
{
	uint8_t result;
	__asm__ volatile("inb %1, %0" : "=a"(result) : "dN"(port));
	return result;
}

volatile void outb(uint16_t port, uint8_t data)
{
	__asm__ volatile("outb %1, %0" : : "dN"(port), "a"(data));
}

volatile uint16_t inw(uint16_t port)
{
	uint16_t result;
	__asm__ volatile("inw %1, %0" : "=a"(result) : "dN"(port));
	return result;
}

volatile void outl(uint16_t port, uint32_t data)
{
	__asm__ volatile("outl %0, %1" : : "a"(data), "dN"(port));
}

volatile void inl(uint16_t port)
{
        uint32_t value;
        __asm__ __volatile__("inl %1, %0"
                                : "=a"(value) // Output: Store the result in `value` (EAX register)
                                : "dN"(port)); // Input: Port number in `DX` register
        return value;
}

void outw(unsigned short port, unsigned short value)
{
	asm volatile (
	        "outw %0, %1"
	        :
	        : "a"(value), "Nd"(port)
	);
}

void insl(uint16_t port, void* addr, int count)
{
	asm volatile ("cld; rep insl"
	              : "=D" (addr), "=c" (count)
	              : "d" (port), "0" (addr), "1" (count)
	              : "memory");
}


