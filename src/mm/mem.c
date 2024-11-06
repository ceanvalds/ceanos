#include "pmm.h"

void initMemory(uint32_t memHigh, uint32_t physicalAllocStart) {
    // Initialize physical memory manager
    pmm_init(0, memHigh);
    
    // Mark kernel pages as used
    uint32_t kernelPages = CEIL_DIV(physicalAllocStart, 0x1000);
    for (uint32_t i = 0; i < kernelPages; i++) {
        physicalMemoryBitmap[i / 8] |= (1 << (i % 8));
        totalAlloc++;
    }
}

uint32_t pmmAllocPageFrame() {
    // Find first free frame
    for (uint32_t i = pageFrameMin; i < pageFrameMax; i++) {
        if (!(physicalMemoryBitmap[i / 8] & (1 << (i % 8)))) {
            physicalMemoryBitmap[i / 8] |= (1 << (i % 8));
            totalAlloc++;
            return i * 0x1000;
        }
    }
    return 0;
}

void invalidate(uint32_t vaddr) {
    asm volatile("invlpg (%0)" :: "r" (vaddr) : "memory");
} 