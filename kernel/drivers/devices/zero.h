//@brief /dev/zero device creator
#pragma once

#include "vfs.h"

void create_zero_dev();
int zero_open(vfs_node *node);
int zero_close(vfs_node *node);
ssize_t zero_read(vfs_node *node,uint32_t offset,uint32_t count,void *buffer);
ssize_t zero_write(vfs_node *node,uint32_t offset,uint32_t count,void *buffer);
