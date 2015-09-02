use std::fs;
use std::fs::{File, OpenOptions};
use std::io;
use std::io::prelude::*;
use std::os::unix;
use std::path::Path;

fn cat(path: &Path) -> io::Result<String> {
    let mut f = try!(File::open(path));
    let mut s = String::new();
    match f.read_to_string(&mut s) {
        Ok(_) => Ok(s),
        Err(e) => Err(e),
    }
}

fn echo(s: &str, path: &Path) -> io::Result<()> {
    let mut f = try!(File::create(path));
    f.write_all(s.as_bytes())

}

fn touch(path: &Path) -> io::Result<()> {
    match OpenOptions::new().create(true).open(path) {
        Ok(_) => Ok(()),
        Err(e) => Err(e),
    }
}

fn main() {
    println!("mkdir a ");
    match fs::create_dir("a") {
         Err(why)=> println!("!{:?}", why.kind()),
         Ok(_) =>{},
    }

    println!("echo hello > a/b.tct");
    echo("hello", &Path::new("a/b.txt")).unwrap_or_else(|why|{
        println!("!{:?}", why.kind());
    });

    println!("mkdir -p a/c/d");

    fs::create_dir("a/c/d").unwrap_or_else(|why|{
        println!("!{:?}", why.kind());
    });
}
