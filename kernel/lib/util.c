#include <stdint.h>
#include <util.h>
#include <timer.h>
#include <stdlib/stdio.h>

void dump_registers()
{
	struct registers_for_dump regs;

	asm volatile (
	        "mov %%eax, %[eax]\n\t"
	        "mov %%ebx, %[ebx]\n\t"
	        "mov %%ecx, %[ecx]\n\t"
	        "mov %%edx, %[edx]\n\t"
	        "mov %%esi, %[esi]\n\t"
	        "mov %%edi, %[edi]\n\t"
	        "mov %%ebp, %[ebp]\n\t"
	        "mov %%esp, %[esp]\n\t"
	        "pushf\n\t"              
	        "pop %[eflags]\n\t"      
	        "mov %%cs, %[cs]\n\t"    
	        "mov %%ds, %[ds]\n\t"    
	        "mov %%es, %[es]\n\t"    
	        "mov %%fs, %[fs]\n\t"    
	        "mov %%gs, %[gs]\n\t"    
	        "mov %%ss, %[ss]\n\t"    
	        :
	        [eax] "=g" (regs.eax),
	        [ebx] "=g" (regs.ebx),
	        [ecx] "=g" (regs.ecx),
	        [edx] "=g" (regs.edx),
	        [esi] "=g" (regs.esi),
	        [edi] "=g" (regs.edi),
	        [ebp] "=g" (regs.ebp),
	        [esp] "=g" (regs.esp),
	        [eflags] "=g" (regs.eflags),
	        [cs] "=g" (regs.cs),
	        [ds] "=g" (regs.ds),
	        [es] "=g" (regs.es),
	        [fs] "=g" (regs.fs),
	        [gs] "=g" (regs.gs),
	        [ss] "=g" (regs.ss)
	        :
	        : "memory"
	);

	__printf("\ndumping registers:\n");
	__printf("\teax: 0x%d\n", regs.eax);
	__printf("\tebx: 0x%d\n", regs.ebx);
	__printf("\tecx: 0x%d\n", regs.ecx);
	__printf("\tedx: 0x%d\n", regs.edx);
	__printf("\tesi: 0x%d\n", regs.esi);
	__printf("\tedi: 0x%d\n", regs.edi);
	__printf("\tebp: 0x%d\n", regs.ebp);
	__printf("\tesp: 0x%d\n", regs.esp);
	__printf("\teip: unavailable\n");
	__printf("\teflags: 0x%d\n", regs.eflags);
	__printf("\ts: 0x%d\n", regs.cs);
	__printf("\tds: 0x%d\n", regs.ds);
	__printf("\tes: 0x%d\n", regs.es);
	__printf("\tfs: 0x%d\n", regs.fs);
	__printf("\tgs: 0x%d\n", regs.gs);
	__printf("\tss: 0x%d\n", regs.ss);
}

uint32_t get_eip()
{
	uint32_t eip;

	asm volatile (
	        "call 1f\n\t"
	        "1:\n\t"
	        "pop %0\n\t"
	        : "=r" (eip)
	        :
	        :
	);

	return eip;
}

void* __memcpy(void* dest, const void* src, size_t n) {
    unsigned char* d = dest;
    const unsigned char* s = src;

    while (n--) {
        *d++ = *s++;
    }
    
    return dest;
}

int __memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *p = ptr1;
	const unsigned char *q = ptr2;

	while (num > 0) {
		if (*p != *q)
			return (*p - *q);
		num--;
		p++;
		q++;
	}
	return 0;
}

void __memset(void *dest, char val, uint32_t count)
{
	char *temp = (char*) dest;
	for (; count != 0; count --) {
		*temp++ = val;
	}
}

void* __memmove(void* dest, const void* src, uint32_t len)
{
	uint8_t* d = (uint8_t*)dest;
	const uint8_t* s = (const uint8_t*)src;

	if (d < s) {
		while (len >= 4) {
			*(uint32_t*)d = *(const uint32_t*)s;
			d += 4;
			s += 4;
			len -= 4;
		}

		if (len >= 2) {
			*(uint16_t*)d = *(const uint16_t*)s;
			d += 2;
			s += 2;
			len -= 2;
		}

		if (len > 0) {
			*d = *s;
		}
	} else {
		d += len;
		s += len;

		while (len >= 4) {
			d -= 4;
			s -= 4;
			*(uint32_t*)d = *(const uint32_t*)s;
			len -= 4;
		}

		if (len >= 2) {
			d -= 2;
			s -= 2;
			*(uint16_t*)d = *(const uint16_t*)s;
			len -= 2;
		}

		if (len > 0) {
			d--;
			s--;
			*d = *s;
		}
	}

	return dest;
}

void outPortB(uint16_t Port, uint8_t Value)
{
	asm volatile ("outb %1, %0" : : "dN" (Port), "a" (Value));
}

char inPortB(uint16_t port)
{
	char rv;
	asm volatile("inb %1, %0": "=a"(rv):"dN"(port));
	return rv;
}
