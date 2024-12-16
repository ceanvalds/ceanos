//@file kernel.c
//@brief entry point of ceanos kernel
//@author ceanvalds

/* SYSTEM */

#include <sys/call/syscall.h>
#include <sys/proc/process.h>
#include <sys/proc/scheduler.h>
#include <multiboot.h>
#include <timer.h>
#include "kernel.h" 

/* DESCRIPTOR TABLES */

#include <gdt.h>
#include <idt.h>

/* DRIVERS  */

#include <drivers/storage/ata.h>
#include <drivers/video/vga/vga.h>
#include <drivers/kb/kbps2.h>
#include <drivers/video/vga/vga_types.h>

#include <drivers/devices/serial.h>
#include <drivers/devices/dev.h>

// #include <drivers/generic/pci.h>

/* MEMORY */

#include <mm/malloc.h>
#include <mm/paging.h>
#include <mm/mem.h>

/* FILE SYSTEMS */

#include <fs/fat.h>
#include <fs/vfs.h>
#include <fs/tmpfs.h>

/* STDLIB */

#include <stdlib/stdio.h>
#include <stdlib/string.h>

/* UTILS */

#include <stdint.h>
#include <util.h>
#include <io.h>

/* OPTIONS */
#include <compiler.h>
#include "config.h"
#include <kernel.h>

// actual code

void main(uint32_t magic, struct multiboot_info* boot);
char prompt[2] = "% ";

bool debug_mode;

// Initialize all the important stuff, like idt, gdt, etc

static void init_mm(struct multiboot_info* boot)
{
	//calculate physical memory start for kernel heap
	uint32_t mod1 = *(uint32_t*)(boot->mods_addr + 4);
	uint32_t physicalAllocStart = (mod1 + 0xFFF) & ~0xFFF;
	initMemory(boot->mem_upper * 1024, physicalAllocStart);
	kmallocInit(0x4000);
    	debugf("[mm] memory done!\n");
}

static void init_tables()
{
	gdt_init();
	idt_init();
}

static void init_all(struct multiboot_info* boot)
{
	#ifdef DEBUG
	debug_mode = true;
	#endif

	vga_disable_cursor();
        
        init_tables();

	timer_init();
	keyboard_init();
	init_mm(boot);

	vfs_init();
	init_tmpfs();

        init_devices(); 
        InitPci();

	__printf("[ceanos] OK\n");

	sleep(750);
	Reset();
}

void enable_default(struct multiboot_info* boot)
{
	init_all(boot);

	__printf("                               CeanOS V%s\n", VERSION);       // This part will be replaced with 
	__printf("                        Public Domain Operating System\n\n"); // a shell executable, but for now
        
        __printf("Do 'help' for more info \n");
        __printf("ceanos%s", prompt);		                                // it will just print a message

	set_screen_color(0x0F);
}

public void main(uint32_t magic, struct multiboot_info* boot)
{
        #define __ceanos__
                enable_default(boot);

        extern uint64_t ticks;   

	while(1) {
		// TODO: Add a way to check for stack overflows and other errors that the ISR can't handle
                ticks++;
        };
}

char *__terry[] = { "CIA", "nigger", "its", "terry", "a", "is", "glowies", "car", "wtf", "fuck", "cool", "niggerville", "niggertopia", "ethan", "the", "schizophrenia", "chocolate", "ok", "God", "I", "am", "doctors", "fucking", "jedi", "HolyC", "TempleOS", "Terry Davis", "gay", "C", "you're", "gcc", "sucks", "hamburger", "smart", "smartest", "programmer", "that", "has", "ever", "live", "lived", "impossible", "possible", "linus", "torvalds", "mr.", ".", "?", "!", ",", "FBI", "data", "ghost", "default", "no", "yes", "are", "make", "way", "discord", "censers", "deafness", "medea", "windus", "submit", "remorse", "acquaintance", "succeded", "valuable", "fingers", "garden", "ceanos", "linux", "vim", "emacs", "do", "while", "keep", "anti-cia", "perpetuators", "thick", "america", "mafia", "computer", "IBM", "commodore-64", "compiler", "divine", "wisdom", "intellect", "minecraft", "ISS", "Feds", "Diddy", "Oil", "Baby", "war", "peace", "game", "Jesus", "Bible", "spartan", "IRS", "USA", "qwerty", "azerty", "qwertz", "imagine", "using", "windows", "ubuntu", "arch", "alpine", "nixos", "of course", "add", "tcp", "IP", "VPN", "protocol", "hymn", "array", "map", "go", "code", "stop", "wasting", "time", "king", "terrible", "I am King Terry the Terrible", "The CIA", "The CIA will be executed with an A10 gun, the fist of God", "fist", "of", "will", "be", "executed", "mental", "problems", "glow", "in", "dark", "you", "can", "see", "them", "if", "driving", "make", "gun", "half", "life", "chosen", "God's", "proceed", "say" };

const size_t __TERRY_ARRAY_SIZE = sizeof(__terry) / sizeof(__terry[0]);

