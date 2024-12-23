#include "fat.h"
#include <stdint.h>
#include <stdlib/stdio.h>
#include <mm/malloc.h>
#include <storage/ata.h>
#include <util.h>

void read_boot_sector(uint32_t LBA, BootSector *boot_sector) {
        uint8_t boot_sector_data[512];
        read_sectors_ATA_PIO(boot_sector_data, LBA, 1);
        __memcpy(boot_sector, boot_sector_data, sizeof(BootSector));

        __printf("bytes per sector: %d\n", boot_sector->bytes_per_sector);
        __printf("sectors per cluster: %d\n", boot_sector->sectors_per_cluster);
        __printf("root cluster: %u\n", boot_sector->root_cluster);
}

