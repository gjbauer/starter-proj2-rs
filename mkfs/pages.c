// based on cs3650 starter code

#define _GNU_SOURCE
#include <string.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdint.h>

#include "pages.h"
#include "util.h"
#include "bitmap.h"
#include "mkfs.h"
#include "inode.h"

const int PAGE_COUNT = 512;
const int NUFS_SIZE  = 4096 * 512; // 2MB

static int   pages_fd   = -1;
static void* pages_base =  0;

void
pages_init(const char* path)
{
    pages_fd = open(path, O_CREAT | O_RDWR, 0644);
    assert(pages_fd != -1);

    int rv = ftruncate(pages_fd, NUFS_SIZE);
    assert(rv == 0);

    pages_base = mmap(0, NUFS_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pages_fd, 0);
    assert(pages_base != MAP_FAILED);

    void* pbm = get_pages_bitmap();
    for (int i=0; i<=9; i++) alloc_page();
    void* ibm = get_inode_bitmap();
    for (int i=0; i<=512; i++) bitmap_put(ibm, i, 0);
    inode ins;
    void* in = get_inode_start();
    for (int i=0; i<=512; i++) {
    	ins.inum=i;
    	ins.size[0]=0, ins.size[1]=0;
	ins.ptrs[0]=0, ins.ptrs[1]=0;
    	memcpy(((inode*)in+i), &ins, sizeof(ins));
    }
    
}

void
storage_init(const char* path)
{
    pages_fd = open(path, O_RDWR, 0644);
    if (pages_fd == -1) {
    	mkfs();
    	storage_init(path);
    }

    pages_base = mmap(0, NUFS_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, pages_fd, 0);
    assert(pages_base != MAP_FAILED);
}

void
pages_free()
{
    int rv = munmap(pages_base, NUFS_SIZE);
    assert(rv == 0);
}

void*
pages_get_page(int pnum)
{
    return pages_base + 4096 * pnum;
}

void*
get_pages_bitmap()
{
    return pages_get_page(0);
}

void*
get_inode_bitmap()
{
    return pages_get_page(1);
}

void*
get_inode_start()
{
    return pages_get_page(2);
}

void*
get_root_start()
{
    return pages_get_page(5);
}

int
alloc_page()
{
    void* pbm = get_pages_bitmap();

    for (int ii = 1; ii < PAGE_COUNT; ++ii) {
        if (!bitmap_get(pbm, ii)) {
            bitmap_put(pbm, ii, 1);
            printf("+ alloc_page() -> %d\n", ii);
            return ii;
        }
    }

    return -1;
}

void
free_page(int pnum)
{
    printf("+ free_page(%d)\n", pnum);
    void* pbm = get_pages_bitmap();
    bitmap_put(pbm, pnum, 0);
}

