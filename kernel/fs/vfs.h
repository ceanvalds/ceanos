#pragma once

#define MAX_FILES 100
#define MAX_FILE_SIZE 1024
#define MAX_FILE_NAME 32
#define VFS_SPECIAL_PATH_SELF "."
#define VFS_SPECIAL_PATH_PARENT ".."

#include <stdint.h>
#include <util.h>
#include <list.h>
#include <types.h>

#ifndef VFS_DRIVER
// this part should only be defined when VFS_DRIVER is NOT defined
struct inode_struct {
    int inode;
    char name[256];
    struct inode_struct *parent;
    struct inode_struct *child;
    struct inode_struct *brother;
    int size;
    int type;
};
#endif

struct vfs_node_struct;
typedef struct inode_struct inode;

//type of nodes
#define VFS_NODE_TYPE_FILE 0x01
#define VFS_NODE_TYPE_FOLDER 0x02
#define VFS_NODE_TYPE_MOUNT_POINT 0x04
#define VFS_NODE_TYPE_PIPE 0x08
#define VFS_NODE_TYPE_SYMLINK 0x10
#define VFS_NODE_TYPE_CHAR_DEVICE 0x20

//functions
typedef ssize_t (*read_type_t) (struct vfs_node_struct *,  off_t, size_t, void *);
typedef ssize_t (*write_type_t) (struct vfs_node_struct *, off_t, size_t, void *);
typedef int (*open_type_t) (struct vfs_node_struct *);
typedef void (*close_type_t) (struct vfs_node_struct *);
typedef int (*create_type_t) (struct vfs_node_struct *, char *name, mode_t permission);
typedef int (*unlink_type_t) (struct vfs_node_struct *, char *name);
typedef int (*mkdir_type_t) (struct vfs_node_struct *, char *name, mode_t permission);
typedef int (*chmod_type_t) (struct vfs_node_struct *, mode_t mode);
typedef int (*chown_type_t) (struct vfs_node_struct *, uid_t, gid_t);
typedef int (*set_size_type_t) (struct vfs_node_struct *,size_t);
typedef struct dirent *(*readdir_type_t) (struct vfs_node_struct *, uint32_t);
typedef struct vfs_node_struct *(*finddir_type_t) (struct vfs_node_struct *, char *name);

typedef struct vfs_node_struct {
    char name[256];
    uid_t owner;
    gid_t group_owner;
    size_t size;
    struct inode_struct *inode;
    uint32_t children_count;
    struct vfs_node_struct *child;
    struct vfs_node_struct *parent;
    struct vfs_node_struct *brother;
    time_t create_time;
    time_t access_time;
    time_t modify_time;
    uint32_t ref_count;
    uint32_t driver;
    read_type_t read;
    write_type_t write;
    open_type_t open;
    close_type_t close;
    create_type_t create;
    mkdir_type_t mkdir;
    unlink_type_t unlink;
    set_size_type_t set_size;
    chown_type_t chown;
    chmod_type_t chmod;
    readdir_type_t readdir;
    finddir_type_t finddir;
    mode_t permission;
    uint8_t type;
} vfs_node;

extern vfs_node *vfs_root_node;

int vfs_init();
vfs_node *kopen(const char *path);
int vfs_mount(char *path, vfs_node *node);

struct dirrent *vfs_readdir(vfs_node *node,uint32_t index);
struct vfs_node_struct *vfs_finddir(vfs_node *node,char *name);
ssize_t vfs_read(vfs_node *node, off_t offset, size_t count, void *buffer);
ssize_t vfs_write(vfs_node *node, off_t offset, size_t count, void *buffer);
int vfs_open(vfs_node *node);
int vfs_close(vfs_node *node);
int vfs_create(vfs_node *node,char *name, mode_t permission);
int vfs_mkdir(vfs_node *node,char *name, mode_t permission);
int vfs_unlink(vfs_node *node,char *name);
int vfs_set_size(vfs_node *node, size_t new_size);
int vfs_chown(vfs_node *node, uid_t user, gid_t group);
int vfs_chmod(vfs_node *node, mode_t permission);
