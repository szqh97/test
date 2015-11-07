use std::convert::From;
use std::error::Error;
use std::fs;
use std::io;
use std::num;
pub fn main() {
    let string: String = From::from("foo");
    let bytes: Vec<u8> = From::from("foo");
    let cow: ::std::borrow::Cow<str> = From::from("foo");

    println!("{}", string);
    println!("{:?}", bytes);
    println!("{:?}", cow);

    let io_err: io::Error = io::Error::last_os_error();
    let parse_err: num::ParseIntError = "not a number".parse::<i32>().unwrap_err();

    let err: Box<Error> = From::from(io_err);
    let err2: Box<Error> = From::from(parse_err);
    println!("{:}", err);
    println!("{:?}", err2);
}
