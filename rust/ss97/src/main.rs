#[macro_use]
extern crate log;
extern crate env_logger;
extern crate errno;
extern crate epoll;
extern crate chrono;

mod shell;
mod EventLoop;

use chrono::UTC;

use shell::*;
fn main() {
    env_logger::init().unwrap();
    println!("Hello, world!");
    test_log();
    info!("starting..");
    warn!("warax");

    println!("{:?}", UTC::now());
    println!("{:?}", UTC::now());
}
