#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define CEIL_DIV(a,b) (((a + b) - 1)/b)

void memset(void *dest, char val, uint32_t count);
void* memmove(void* dest, const void* src, uint32_t len);
void outPortB(uint16_t Port, uint8_t Value);
char inPortB(uint16_t port);
void insl(uint16_t port, void* addr, int count); 
void shutdown(uint16_t port, uint16_t value);
void dump_registers();
uint32_t get_eip();
int memcmp(const void *ptr1, const void *ptr2, size_t num); 
void* memcpy(void* dest, const void* src, size_t n);

struct registers_for_dump {
    uint32_t eax;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
    uint32_t esp;
    uint32_t eip;
    uint32_t eflags;
    uint32_t cs;
    uint32_t ds;
    uint32_t es;
    uint32_t fs;
    uint32_t gs;
    uint32_t ss;
}__attribute__((packed));

struct InterruptRegisters{
    uint32_t cr2;
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, csm, eflags, useresp, ss;
};

#endif //util.h
