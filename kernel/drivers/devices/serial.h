#pragma once
#define COM1 0x3f8
#include <stdint.h>
#include <fs/vfs.h>

int init_serial_dev();
vfs_node *serial_create_device(uint16_t port);
void serial_write_char(char ch,uint16_t port);