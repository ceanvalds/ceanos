#include <stdio.h>
#include <stdint.h>
#include <io.h>

#include "stacktrace.h"

unsigned long getsp() 
{//get stack pointer function 
        unsigned long sp;
        asm volatile("mov %%esp, %0" : "=r" (sp));  
        return sp;
}

void __stack_trace()
{
        unsigned long *stack_ptr = (unsigned long *)getsp();
        stack_ptr++;

        __printf("Stack trace:\n");

        //first 10 addresses
        for (int i = 0; i < 10; i++) {  
                unsigned long return_addr = *stack_ptr;
                __printf("\t0x%u\n", return_addr);
                stack_ptr++;
        }

        __printf("stack tracing complete\n");
}
