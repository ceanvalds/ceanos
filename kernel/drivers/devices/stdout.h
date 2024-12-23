#pragma once
#include "vfs.h"

int create_stdout_dev();
int stdout_open(vfs_node *node);
int stdout_close(vfs_node *node);
ssize_t stdout_write(vfs_node *node,off_t offset, size_t count,char *buffer);
