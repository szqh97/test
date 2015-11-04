use std::thread;

pub fn function_name() {
    
    thread::Builder::new().name("child1".to_string()).spawn(move || {
        println!("Hello, world!");
        println!("{}", thread::current().name().unwrap());
    });
    println!("thread name {}", thread::current().name().unwrap());
}

pub fn main() {
    function_name();
    
}
