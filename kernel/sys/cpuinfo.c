#include <stdint.h>
#include <stdio.h>
#include "cpuinfo.h"

void get_cpu_info(CPUinfo* cpu_info) {
        uint32_t eax, ebx, ecx, edx;

        asm volatile(
                "cpuid"
                : "=a"(eax), "=b"(ebx), "=c"(ecx), "=d"(edx)
                : "a"(0)
        );

        *((uint32_t*)&cpu_info->vendor[0]) = ebx;
        *((uint32_t*)&cpu_info->vendor[4]) = edx;
        *((uint32_t*)&cpu_info->vendor[8]) = ecx;
        cpu_info->vendor[12] = '\0';

        asm volatile(
                "cpuid"
                : "=a"(eax)
                : "a"(1)
        );
        cpu_info->model = (eax >> 4) & 0xF;
        cpu_info->family = (eax >> 8) & 0xF;

        // brand (eax 0x80000002 to 0x80000004)
        uint32_t* brand_ptr = (uint32_t*)cpu_info->brand;
        for (int i = 0; i < 3; i++) {
                asm volatile(
                "cpuid"
                : "=a"(brand_ptr[0]), "=b"(brand_ptr[1]), "=c"(brand_ptr[2]), "=d"(brand_ptr[3])
                : "a"(0x80000002 + i)
                );
                brand_ptr += 4;
        }
        cpu_info->brand[48] = '\0'; 
}

inline void print_cpuinfo() {
        CPUinfo cpu_info;
        get_cpu_info(&cpu_info);

        __printf("\nCPU: \n - %s\n - %s\n - Model: %u\n - Family: %u\n",
                cpu_info.brand, cpu_info.vendor, cpu_info.model, cpu_info.family);
}
