#include "gdt.h"
#include <util.h>
#include <drivers/video/vga/vga.h>

#define GDT_DATA_SEGMENT 0x10

extern void tss_flush();

struct gdt_entry_struct gdt_entries[6];
struct gdt_ptr_struct gdt_ptr;
struct tss_entry_struct tss_entry;

void gdt_init()
{
	gdt_ptr.limit = (sizeof(struct gdt_entry_struct) * 6) - 1;
	gdt_ptr.base = (uint32_t)&gdt_entries;

	setGdtGate(0,0,0,0,0); //null segment
	setGdtGate(1,0,0xFFFFFFFF, 0x9A, 0xCF); //kernel code segment
	setGdtGate(2,0,0xFFFFFFFF, 0x92, 0xCF); //kernel data segment
	setGdtGate(3,0,0xFFFFFFFF, 0xFA, 0xCF); //user code segment
	setGdtGate(4,0,0xFFFFFFFF, 0xF2, 0xCF); //user data segment
	writeTSS(5,0x10, 0x0);

	gdt_flush((uint32_t)&gdt_ptr);
	__printf("[gdt] OK\n");
	tss_flush();
	__printf("[tss] OK\n");
}


void writeTSS(uint32_t num, uint16_t ss0, uint32_t esp0)
{
    uint32_t base = (uint32_t) &tss_entry;
    uint32_t limit = base + sizeof(tss_entry);

    setGdtGate(num, base, limit, 0xE9, 0x00);  
    __memset(&tss_entry, 0, sizeof(tss_entry));

    tss_entry.ss0 = ss0;
    tss_entry.esp0 = esp0;

    tss_entry.cs = 0x08 | 0x3;  
    tss_entry.ss = tss_entry.ds = tss_entry.es = tss_entry.fs = tss_entry.gs = 0x10 | 0x3;  
}


void setGdtGate(uint32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
	gdt_entries[num].base_low = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high = (base >> 24) & 0xFF;

	gdt_entries[num].limit = (limit & 0xFFFF);
	gdt_entries[num].flags = (limit >> 16) & 0x0F;
	gdt_entries[num].flags |= (gran & 0xF0);

	gdt_entries[num].access = access;
}

void gdt_flush(struct gdt_ptr_struct* gdt_ptr)
{
  __asm__ volatile(
    "lgdt (%0)\n" // Loading gdt

    "ljmp $0x08, $.Lflush\n" // Far Jump for CS register

    ".Lflush:\n"

    /*
     *
     * Segment registers config
     *
     */

    "movw %1, %%ax\n"
    "movw %%ax, %%es\n"
    "movw %%ax, %%ss\n"
    "movw %%ax, %%ds\n"
    "movw %%ax, %%fs\n"
    "movw %%ax, %%gs\n"
    :
    :"r"(gdt_ptr), "i"(GDT_DATA_SEGMENT) 
    : "%ax"
  );
}
