use std::io;
use std::io::prelude::*;
use std::fs::File;

#[macro_use]
pub fn read_test() {
    let mut f = match File::open("./Cargo.toml") {
        Ok(f) => f, 
        Err(_) => panic!("no such file"),
    };
    let mut file = try!(File::open("./Cargo.toml").map_err(|e| e.to_string()));
    //let mut f1 = try!(File::open("Cargo.toml"));
    let mut buff = [0;10];
    
    f.read(&mut buff[..]);
    //try!(f.read(&mut buff[..]));

    println!("{:?}", &buff[..]);
}

pub fn main() {
    read_test();
}
