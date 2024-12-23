#include <errno.h>
#include "dev.h"
#include <stdlib/stdio.h>
#include <fs/vfs.h>
#include "serial.h"
#include <mm/malloc.h>

int init_devices(){
        //first create /dev directory
        vfs_node *root_node = kopen("/");
        if(root_node == NULL) {
                __printf("[dev] FAIL \n");
                return ERR_CANT_OPEN;
        }

        debugf("[dev] making /dev directory\n");

        vfs_mkdir(root_node, "dev", 0777);
        vfs_close(root_node);

        //init_serial_dev();

        __printf("[dev] OK\n");
}
