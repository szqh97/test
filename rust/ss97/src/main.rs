#[macro_use]
extern crate log;
extern crate env_logger;
mod shell;
use shell::test_log;
fn main() {
    env_logger::init().unwrap();
    println!("Hello, world!");
    test_log();
    info!("starting..");
    warn!("warax");
}
