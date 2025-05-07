use arrayvec::ArrayString;
const DIR_NAME: u16 = 48;
/*
typedef struct dirent {
    char name[DIR_NAME];
    int  inum;
    char _reserved[12];
} dirent;
*/

struct Dirent {
	name: ArrayString<DIR_NAME>,
	inum: u16,
}
