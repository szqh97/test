use std::error::Error;
use std::io::prelude::*;
use std::process::{Command, Stdin};
static PANGRAM: &'static str = "the quick brown fox jump over the lazy dog.\n";

fn main() {
    let process = match Command::new("wc")
                                .stdin(Stdin::piped())
                                .stdout(Stdio::piped())
                                .spawn(){
         Err(Why) => panic!("counldn't spawn wc: {}"),
         Ok(_) => println!("send program to wc");

    }
}
