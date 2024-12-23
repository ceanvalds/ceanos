#include "stdout.h"
#include "malloc.h"
#include "stdio.h"

int create_stdout_dev(){
    //first open the dev folder and create a file
    vfs_node *dev_node = kopen("/dev");
    if(dev_node == NULL)return -1;
    vfs_create(dev_node,"stdout",777);
    vfs_close(dev_node);

    //create the stdout node and mount it
    vfs_node *node = new(vfs_node);
    node->open = stdout_open;
    node->close = stdout_close;
    node->type = VFS_NODE_TYPE_CHAR_DEVICE;
    node->write = stdout_write;
    node->read = NULL;
    vfs_mount("/dev/stdout",node);
    return 0;
}

int stdout_open(vfs_node *node){
    return 0;
}

int stdout_close(vfs_node *node){
    return 0;
}

ssize_t stdout_write(vfs_node *node,off_t offset, size_t count,char *buffer){
    //print to the sreen
    for(uint32_t i=0;i<count;i++){
        __putc(buffer[i]);
    }
    
    return count;
}
