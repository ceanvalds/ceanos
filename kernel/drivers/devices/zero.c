#include "zero.h"
#include "vfs.h"
#include "malloc.h"

void create_zero_dev(){
    vfs_node *dev = kopen("/dev");
    vfs_create(dev,"zero",777);
    vfs_close(dev);

    //create an custom node for it
    vfs_node *node = new(vfs_node);
    node->open = zero_open;
    node->close = zero_close;
    node->read = zero_read;
    node->write = zero_write;
    node->type = VFS_NODE_TYPE_CHAR_DEVICE;

    vfs_mount("/dev/zero",node);
}
int zero_open(vfs_node *node){
    return 0;
}

int zero_close(vfs_node *node){
    return 0;
}

ssize_t zero_read(vfs_node *node,uint32_t offset,uint32_t count,void *buffer){
    //TODO make this faster
    //by taking all avantage of 32 bit cpu bus
    //
    //basicly just fill the given buffer
    //with zeros
    char *buf = (char *)buffer;
    uint32_t i = 0;
    while(i<count) buf[i++]=0;
    return count;
}
ssize_t zero_write(vfs_node *node,uint32_t offset,uint32_t count,void *buffer){
    //actually don't write anything
    //but don't tell it
    return count ;
}
