#include "context.h"   
#include <stdint.h>

typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, ebp;   
    uint32_t esp, eip;                             
    uint32_t cs, ds, es, fs, gs;                   
} context_t;


