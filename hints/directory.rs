
pub const DIR_NAME: usize = 48;

pub struct Dirent {
	pub name: [char; DIR_NAME],
	pub inum: u16,
	pub active: bool,
}

pub fn dirent_deserialize(mmap: &memmap2::MmapMut, offset: usize) -> Dirent {
	// TODO: Implement dirent_deserialize...
}
