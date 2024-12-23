#pragma once

#include <stdint.h>

typedef struct {
    uint8_t jump[3];
    uint8_t oem[8];
    uint16_t bytes_per_sector;
    uint8_t sectors_per_cluster;
    uint16_t reserved_sectors;
    uint8_t fat_count;
    uint16_t root_entries;
    uint16_t total_sectors;
    uint8_t media_descriptor;
    uint16_t fat_size;
    uint16_t sectors_per_track;
    uint16_t head_count;
    uint32_t hidden_sectors;
    uint32_t total_sectors_fat32;
    uint32_t fat_start_lba;
    uint16_t fat_size_fat32;
    uint16_t ext_flags;
    uint16_t fs_version;
    uint32_t root_cluster;
    uint16_t fsinfo_sector;
    uint16_t backup_boot_sector;
    uint8_t reserved[12];
    uint8_t drive_number;
    uint8_t reserved1;
    uint8_t boot_signature;
    uint32_t volume_id;
    uint8_t volume_label[11];
    uint8_t fs_type[8];
    uint8_t boot_code[420];
    uint16_t boot_sector_signature;
} __attribute__((packed)) BootSector;

typedef struct {
    uint8_t name[8];           // File name (8 characters)
    uint8_t ext[3];            // File extension (3 characters)
    uint8_t attributes;        // File attributes (read-only, hidden, system, etc.)
    uint8_t reserved;          // Reserved
    uint8_t creation_time_tenth; // Creation time (tenths of a second)
    uint16_t creation_time;    // Creation time
    uint16_t creation_date;    // Creation date
    uint16_t last_access_date; // Last access date
    uint16_t first_cluster_hi; // High 16 bits of the first cluster number
    uint16_t write_time;       // Last write time
    uint16_t write_date;       // Last write date
    uint16_t first_cluster_lo; // Low 16 bits of the first cluster number
    uint32_t file_size;        // File size in bytes
} __attribute__((packed)) DirectoryEntry;

 
