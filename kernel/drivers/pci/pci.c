#include <stdint.h>
#include <stdio.h>
#include <io.h>
#include <vfs.h>

#include <errno.h>
#include <kernel.h>

uint16_t pciConfigReadWord(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
        uint32_t address;
        uint32_t lbus  = (uint32_t)bus;
        uint32_t lslot = (uint32_t)slot;
        uint32_t lfunc = (uint32_t)func;
        uint16_t tmp = 0;
  
        // Create configuration address
        address = (uint32_t)((lbus << 16) | (lslot << 11) |
                (lfunc << 8) | (offset & 0xFC) | ((uint32_t)0x80000000));
  
        // Write out the address
        outl(0xCF8, address);
        
        // Read in the data
        // (offset & 2) * 8) = 0 will choose the first word of the 32-bit register
        tmp = (uint16_t)((inl(0xCFC) >> ((offset & 2) * 8)) & 0xFFFF);
        return tmp;
}

uint32_t InitPci() {
        vfs_node *dev = kopen("/dev");
        vfs_mkdir(dev, "pci", 555);                 //555 - only superusers (root)
        vfs_close(dev);
        
        __printf("[PCI] created *pci_device node\n");

        __printf("[PCI] mounted pci_device node on /dev/pci\n");

        return SUCCESS; 
}

