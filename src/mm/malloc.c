#include "mm/mem.h"

void* kmalloc(size_t size) {
    if (!kmallocInitalized) return NULL;
    
    // Align size to 4 bytes
    size = (size + 3) & ~3;
    
    uint32_t current = heapStart;
    while (current < heapStart + heapSize) {
        uint32_t* header = (uint32_t*)current;
        uint32_t blockSize = *header & ~1;
        
        if (!(*header & 1) && blockSize >= size) {
            if (blockSize > size + 8) {
                // Split block
                uint32_t* newHeader = (uint32_t*)(current + size + 4);
                *newHeader = blockSize - size - 4;
                *header = size | 1;
            } else {
                *header |= 1;
            }
            return (void*)(current + 4);
        }
        current += (*header & ~1) + 4;
    }
    
    // Need more memory
    uint32_t required = size + 4;
    changeHeapSize(heapSize + required);
    return kmalloc(size);
}

void kfree(void* ptr) {
    if (!ptr) return;
    
    uint32_t* header = (uint32_t*)((uint32_t)ptr - 4);
    *header &= ~1;
    
    // Merge with next block if free
    uint32_t current = (uint32_t)header;
    uint32_t next = current + (*header & ~1) + 4;
    if (next < heapStart + heapSize) {
        uint32_t* nextHeader = (uint32_t*)next;
        if (!(*nextHeader & 1)) {
            *header = (*header & ~1) + (*nextHeader & ~1) + 4;
        }
    }
} 