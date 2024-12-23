#pragma once 

#include <stdint.h>

typedef struct {
        char vendor[13];
        char brand[49];
        uint32_t model;
        uint32_t family;
} CPUinfo;

void get_cpu_info(CPUinfo* cpu_info); 
void print_cpuinfo();
