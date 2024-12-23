#ifndef __MALLOC_H__
#define __MALLOC_H__

#include <types.h>
#include <stdint.h>

//the new macro
#define new(type) kmalloc(sizeof(type))

void kmallocInit(uint32_t heapSize);
uint32_t changeHeapSize(int newSize);
void* kmalloc(size_t size);
void kfree(void* ptr);
void debug_mem_graph();

#endif
