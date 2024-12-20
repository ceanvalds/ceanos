#include <stdint.h>
#include <util.h>
#include <idt.h>
#include <stdio.h>
#include "kbps2.h"
#include <drivers/video/vga/vga.h>
#include <vfs.h>



bool capsOn;

bool capsLock;

#include <kernel.h>
const uint32_t KEY_COUNT = 128;
extern char prompt[2];

bool can_type = true;

#include <compiler.h>

char text[512];

const uint32_t UNKNOWN = 0xFFFFFFFF;
const uint32_t ESC = 0xFFFFFFFF - 1;
const uint32_t CTRL = 0xFFFFFFFF - 2;
const uint32_t LSHFT = 0xFFFFFFFF - 3;
const uint32_t RSHFT = 0xFFFFFFFF - 4;
const uint32_t ALT = 0xFFFFFFFF - 5;
const uint32_t F1 = 0xFFFFFFFF - 6;
const uint32_t F2 = 0xFFFFFFFF - 7;
const uint32_t F3 = 0xFFFFFFFF - 8;
const uint32_t F4 = 0xFFFFFFFF - 9;
const uint32_t F5 = 0xFFFFFFFF - 10;
const uint32_t F6 = 0xFFFFFFFF - 11;
const uint32_t F7 = 0xFFFFFFFF - 12;
const uint32_t F8 = 0xFFFFFFFF - 13;
const uint32_t F9 = 0xFFFFFFFF - 14;
const uint32_t F10 = 0xFFFFFFFF - 15;
const uint32_t F11 = 0xFFFFFFFF - 16;
const uint32_t F12 = 0xFFFFFFFF - 17;
const uint32_t SCRLCK = 0xFFFFFFFF - 18;
const uint32_t HOME = 0xFFFFFFFF - 19;
const uint32_t UP = 0xFFFFFFFF - 20;
const uint32_t LEFT = 0xFFFFFFFF - 21;
const uint32_t RIGHT = 0xFFFFFFFF - 22;
const uint32_t DOWN = 0xFFFFFFFF - 23;
const uint32_t PGUP = 0xFFFFFFFF - 24;
const uint32_t PGDOWN = 0xFFFFFFFF - 25;
const uint32_t END = 0xFFFFFFFF - 26;
const uint32_t INS = 0xFFFFFFFF - 27;
const uint32_t DEL = 0xFFFFFFFF - 28;
const uint32_t CAPS = 0xFFFFFFFF - 29;
const uint32_t NONE = 0xFFFFFFFF - 30;
const uint32_t ALTGR = 0xFFFFFFFF - 31;
const uint32_t NUMLCK = 0xFFFFFFFF - 32;

const uint32_t lowercase[128] = {
	UNKNOWN,ESC,'1','2','3','4','5','6','7','8',
	'9','0','-','=','\b','\t','q','w','e','r',
	't','y','u','i','o','p','[',']','\n',CTRL,
	'a','s','d','f','g','h','j','k','l',';',
	'\'','`',LSHFT,'\\','z','x','c','v','b','n','m',',',
	'.','/',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',LEFT,UNKNOWN,RIGHT,
	'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
	UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
	UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
	UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};
const uint32_t uppercase[128] = {
	UNKNOWN,ESC,'!','@','#','$','%','^','&','*','(',')','_','+','\b','\t','Q','W','E','R',
	'T','Y','U','I','O','P','{','}','\n',CTRL,'A','S','D','F','G','H','J','K','L',':','"','~',LSHFT,'|','Z','X','C',
	'V','B','N','M','<','>','?',RSHFT,'*',ALT,' ',CAPS,F1,F2,F3,F4,F5,F6,F7,F8,F9,F10,NUMLCK,SCRLCK,HOME,UP,PGUP,'-',
	LEFT,UNKNOWN,RIGHT,'+',END,DOWN,PGDOWN,INS,DEL,UNKNOWN,UNKNOWN,UNKNOWN,F11,F12,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
	UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
	UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,
	UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN,UNKNOWN
};

const uint32_t val[128] = {'c'};

void append(char *part)
{
	uint8_t i = 0;
	while (text[i] != '\0' && i < sizeof(text) - 1) {
		i++;
	}
	if (i < sizeof(text) - 1) {
		text[i] = part[0];
		text[i + 1] = '\0';
	}
}

void rm()
{
	uint8_t i = 0;
	while(text[i] != '\0') {
		i++;
	}
	text[--i] = '\0';
}

static void clear()
{
	text[0] = '\0';
}


void parser(uint8_t code)
{
	char buff[100];
	uint8_t i = 0;

	char expectedChar = lowercase[code];
	while (text[i] != '\0' && text[i] != expectedChar) {
		buff[i] = text[i];
		i++;
	}
	buff[i] = '\0';

	if (text[i] == expectedChar) {
		print(buff);
	}
}


static void updateTextBuffer(uint8_t code, uint8_t press)
{	
	char charToAdd;
        if (capsOn || capsLock) {
		charToAdd = uppercase[code];
	} else {
		charToAdd = lowercase[code];
	}

	if (press == 0) {
		if (charToAdd == '\n') {
			print("\n");
			run_term(text);
			clear();
				__printf("\nceanos%s", prompt);
		} else {
			__printf("%c", charToAdd);
			append(&charToAdd);
		}
	}
}


/* main keyboard handler function */
static void keyboardHandler(struct InterruptRegisters *regs)
{
        uint8_t scanCode = inPortB(0x60) & 0x7F;
	uint8_t press = inPortB(0x60) & 0x80;

        static bool f7_pressed = false;

	switch(scanCode) {
	case 0x2A:
	case 0x36:
		capsOn = (press == 0);
		break;
	case 0x3A:
		if (press == 0) {
			capsLock = !capsLock;
		}
		break;
	case 0x0E:
		if (press == 0) {
			print("\b");
			rm();
		}
		break;
        case 0x3B:
                CeanOSInfo();
                __printf("ceanos%s", prompt);
                break;
        case 0x41:
                if (press == 0 && !f7_pressed) {  
                    extern uint64_t ticks;
                    srand(ticks);
                    uint32_t __terry_size = __TERRY_ARRAY_SIZE;

                    int index = Ticks() % __terry_size;
                    __printf("%s ", __terry[index]);

                    f7_pressed = true;  
                }
                break;
	default:
		if (press == 0 && scanCode < KEY_COUNT) {
			updateTextBuffer(scanCode, press);
		}
		break;
	}

	if (scanCode == 0x41 && press != 0) {
		f7_pressed = false;
	}
}

void keyboard_init()
{
	capsOn = false;
	capsLock = false;
	idt_install(1, &keyboardHandler);
	clear();
}


