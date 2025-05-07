/*
typedef struct inode {
    int refs; // reference count
    int mode; // permission & type
    int16_t size[2]; // bytes
    int16_t ptrs[2]; // direct pointers
    int iptr; // single indirect pointer
    int inum; // store inum in itself
} inode;
 */
 
struct Inode {
	refs: u32,
	mode: u32,
	size: [u16; 2],
	ptrs: [u16; 2],
	iptr: u32,
	inum: u32,
}
