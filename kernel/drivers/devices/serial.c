#include "serial.h"
#include <fs/vfs.h>
#include <util.h>
#include <errno.h>
#include <stdlib/stdio.h>
#include <mm/malloc.h>

int init_serial_dev(){
    vfs_node *dev = kopen("/dev");
    if(!dev) {
        debugf("[serial] can't open /dev\n");
        return ERR_CANT_OPEN;
    }
    vfs_node *dev_COM1; 
    dev_COM1 = serial_create_device(COM1);
    if(dev_COM1 != NULL) {
        debugf("[serial] COM1 serial port exist try to mount");
        if(!vfs_mount("/dev/COM1",dev_COM1)){
            debugf("[serial] failed to mount COM1");
            kfree(dev_COM1);
        }
    }
    vfs_close(dev);
}

int serial_open(vfs_node *node){
    if(!node->inode) return ERR_CANT_OPEN;
    return SUCCESS;
}

int serial_close(vfs_node *node){
    return SUCCESS;
}

ssize_t serial_write(vfs_node *node,off_t offset, size_t count, char *buffer){
    if(!node) return ERR_BAD_INPUT;
    if(!node->inode) return ERR_CANT_WRITE;
    //ignore offset
    for (uint32_t i = 0; i < count; i++)
    {
        serial_write_char(buffer[i],node->inode);
    }
    return count;
}

vfs_node *serial_create_device(uint16_t port){
    //init the serial port
    outPortB(port + 1, 0x00);
    outPortB(port + 3, 0x80);
    outPortB(port + 0, 0x03);
    outPortB(port + 1, 0x00);
    outPortB(port + 3, 0x03);
    outPortB(port + 2, 0xC7);
    outPortB(port + 4, 0x0B);
    outPortB(port + 4, 0x1E);
    outPortB(port + 0, 0xAE);
    if(inPortB(port + 0) != 0xAE) {
       return NULL;
    }
    outb(port + 4, 0x0F);
 
    vfs_node *node = kmalloc(sizeof(vfs_node));
    node->open = serial_open;
    node->close = serial_close;
    node->readdir = NULL;
    node->finddir = NULL;
    node->write = serial_write;
    node->type = VFS_NODE_TYPE_CHAR_DEVICE;
    node->inode = port;
    return node;
}

void serial_write_char(char ch, uint16_t port){
    //wait
    while(inPortB(port + 5) & 0x20 == 0);
    outPortB(port, ch);
}
