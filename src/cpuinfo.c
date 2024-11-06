#include "cpuinfo.h"

void get_detailed_cpu_info(CPUinfo* cpu_info) {
    uint32_t eax, ebx, ecx, edx;
    
    // Get vendor ID
    asm volatile ("cpuid" 
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) 
        : "a"(0));
        
    *((uint32_t*)&cpu_info->vendor[0]) = ebx;
    *((uint32_t*)&cpu_info->vendor[4]) = edx;
    *((uint32_t*)&cpu_info->vendor[8]) = ecx;
    cpu_info->vendor[12] = '\0';
    
    // Get processor info and feature bits
    asm volatile ("cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(1));
        
    cpu_info->model = (eax >> 4) & 0xF;
    cpu_info->family = (eax >> 8) & 0xF;
    cpu_info->stepping = eax & 0xF;
    cpu_info->extended_model = (eax >> 16) & 0xF;
    cpu_info->extended_family = (eax >> 20) & 0xFF;
} 