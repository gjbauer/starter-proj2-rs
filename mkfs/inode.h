// based on cs3650 starter code

#ifndef INODE_H
#define INODE_H

#include <stdint.h>

#include "pages.h"

typedef struct inode {
    int refs; // reference count
    int mode; // permission & type
    int16_t size[2]; // bytes
    int16_t ptrs[2]; // direct pointers
    int iptr; // single indirect pointer
    int inum; // store inum in itself
} inode;

//void print_inode(inode* node);
inode* get_inode(int inum);
int inode_find(const char *path);
int alloc_inode(const char *path);
//void free_inode();
//int grow_inode(inode* node, int size);
//int shrink_inode(inode* node, int size);
//int inode_get_pnum(inode* node, int fpn);

#endif
