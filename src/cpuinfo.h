#pragma once 

#include <stdint.h>

typedef struct {
    char vendor[30];
    uint32_t model;
    uint32_t family;
    uint32_t stepping;
    uint32_t extended_model;
    uint32_t extended_family;
    uint32_t features;
    uint32_t cache_size;
} CPUinfo;

void get_cpu_info(CPUinfo* cpu_info);
void print_cpuinfo(void);
void print_detailed_cpu_info(void);
void get_detailed_cpu_info(CPUinfo* cpu_info);