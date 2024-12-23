#include "vga.h"
#include "vga_types.h"
#include <stdint.h>
#include <util.h>
#include <io.h>

uint16_t column = 0;
uint16_t line = 0;
uint16_t* const vga = (uint16_t* const) 0xC00B8000;
const uint16_t defaultColor = (COLOR8_WHITE << 8) | (COLOR8_BLACK << 12);
uint16_t currentColor = defaultColor;

inline void Reset()
{
	line = 0;
	column = 0;

	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			vga[y * width + x] = ' ' | defaultColor;
		}
	}
}

inline void newLine()
{
	if (line < height - 1) {
		line++;
		column = 0;
	} else {
		scrollUp();
		column = 0;
	}
}

inline void scrollUp()
{
	for (uint16_t y = 0; y < height; y++) {
		for (uint16_t x = 0; x < width; x++) {
			vga[(y-1) * width + x] = vga[y*width+x];
		}
	}

	for (uint16_t x = 0; x < width; x++) {
		vga[(height-1) * width + x] = ' ' | currentColor;
	}
}

void print(const char* s)
{
	while(*s) {
		switch(*s) {
		case '\n':
			newLine();
			break;
		case '\r':
			column = 0;
			break;
		case '\b':
			if(column == 8) {
				vga[line * width + (++column)] = ' ' | currentColor;
				break;
			}
			if (column == 0 && line != 0) {
				line--;
				column = width;
			}
			vga[line * width + (--column)] = ' ' | currentColor;
			break;
		case '\t':
			if (column == width) {
				newLine();
			}
			uint16_t tabLen = 4 - (column % 4);
			while (tabLen != 0) {
				vga[line * width + (column++)] = ' ' | currentColor;
				tabLen--;
			}
			break;
		default:
			if (column == width) {
				newLine();
			}

			vga[line * width + (column++)] = *s | currentColor;
			break;
		}
		s++;
	}
}

void set_screen_color(uint8_t color)
{
	uint8_t* video_memory = (uint8_t*)0xC00B8000;
	for (int i = 0; i < width * height * 2; i += 2) {
		video_memory[i + 1] = color;
	}
}

void vga_disable_cursor()
{
	// this disables the cursor
	outb(VGA_CRT_IC, 0x0A);
	outb(VGA_CRT_DC, 0x20);
}
