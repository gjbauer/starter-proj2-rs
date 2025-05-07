use fuse::{Filesystem, Mount};
use std::path::Path;
use std::str;

struct SimpleFilesystem;

impl Filesystem for SimpleFilesystem {
    fn stat(&mut self, _path: &Path, _ctx: fuse::Context) -> Result<fuse::StatResult, fuse::Error> {
        // Return information about the root directory
        Ok(fuse::StatResult {
            st_size: 0, // Size of the root directory
            st_mode: 0o777 | fuse::FileType::Directory, // Permissions and type (directory)
            st_nlink: 1, // Number of links
            st_uid: 0,    // User ID
            st_gid: 0,    // Group ID
            st_atim: None, // Access time
            st_mtim: None, // Modification time
            st_ctim: None, // Creation time
        })
    }

    fn getattr(&mut self, path: &Path, _ctx: fuse::Context) -> Result<fuse::StatResult, fuse::Error> {
        match path.as_os_string().into_string() {
            // Return stat information for the root directory
            Ok(ref p) if p == "." => {
                stat(&mut self, &Path::new(p), _ctx);
            }
            _ => {
                println!("Unknown file: {:?}", path);
            }
        }
    }
}

fn main() {
    // Get the mount point from the command line arguments
    let mount_point = std::env::args().nth(1).expect("Usage: <program_name> <mount_point>");

    // Create a new filesystem instance
    let filesystem = SimpleFilesystem;

    // Mount the filesystem
    fuse::mount(filesystem, mount_point.as_str(), &[]).unwrap();
}
