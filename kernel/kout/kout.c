#include <stdio.h>
#include <stdint.h>
#include <drivers/video/vga/vga.h>

#include "kout.h"

void kout(const char *str)
{
        __printf("%s\n", str);
}

void koutd(const char *str)
{
        __printf("[kdebug] %s\n", str);
}

void koutw(const char *str)
{
        __printf("warning: %s\n", str);
}

void koute(const char *str)
{
        __printf("[error] %s\n", str);
}
