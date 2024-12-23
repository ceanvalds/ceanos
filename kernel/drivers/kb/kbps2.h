#ifndef __KBPS2__
#define __KBPS2__

#include <util.h>

void keyboard_init();
static void keyboardHandler(struct InterruptRegisters *regs);
void append(char *part);

#endif