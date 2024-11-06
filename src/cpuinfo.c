#include <stdlib/stdio.h>
#include <cpuinfo.h>

void get_cpu_info(CPUinfo* cpu_info) {
    uint32_t eax, ebx, ecx, edx;
    
    // get vendor ID
    asm volatile ("cpuid" 
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx) 
        : "a"(0));
        
    *((uint32_t*)&cpu_info->vendor[0]) = ebx;
    *((uint32_t*)&cpu_info->vendor[4]) = edx;
    *((uint32_t*)&cpu_info->vendor[8]) = ecx;
    cpu_info->vendor[12] = '\0';
    
    // get processor info and feature bits
    asm volatile ("cpuid"
        : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
        : "a"(1));
        
    cpu_info->model = (eax >> 4) & 0xF;
    cpu_info->family = (eax >> 8) & 0xF;
    cpu_info->stepping = eax & 0xF;
    cpu_info->extended_model = (eax >> 16) & 0xF;
    cpu_info->extended_family = (eax >> 20) & 0xFF;

    printf("CPU vendor: %s\n", cpu_info->vendor);
    printf("model: %d\n", cpu_info->model);
    printf("family: %d\n", cpu_info->family);
    printf("stepping: %d\n", cpu_info->stepping);
    printf("extended model: %d\n", cpu_info->extended_model);
    printf("extended family: %d\n", cpu_info->extended_family);
}
