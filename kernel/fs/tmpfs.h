#pragma once

#include <fs/vfs.h>

int init_tmpfs();

int tmpfs_mkdir(vfs_node *node, char *name,mode_t perm);
int tmpfs_create(vfs_node *node,char name,mode_t perm);
int tmpfs_open(vfs_node *node);
int tmpfs_close(vfs_node *node);
struct dirrent *tmpsfs_readdir(vfs_node *node,uint32_t index);
void tmpfs_debug_inode(inode *node);

vfs_node *tmpfs_inode_to_node(inode *og_inode);
vfs_node *new_tmpfs();
inode *tmpfs_new_inode();
