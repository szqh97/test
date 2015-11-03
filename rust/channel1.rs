use std::thread;
use std::sync::mpsc::channel;
use std::sync::mpsc::sync_channel;

pub fn t1() {
    let (tx, rx) = channel();
    thread::spawn(move|| {
        tx.send(10).unwrap();
    });
    println!("{}", rx.recv().unwrap());

}


pub fn t2() {
    let (tx, rx) = channel();
    for i in 0..10{
        let tx = tx.clone();
        thread::spawn(move||{
            tx.send(i).unwrap();
        });
    }

    for _ in 0..10{
        let j = rx.recv().unwrap();
        println!("recv {}", j);
    }
}

pub fn function_name() {
    let (tx, rx) = sync_channel::<i32>(0);
    thread::spawn(move||{
        tx.send(53).unwrap();
    });
    println!("sync_recv {}", rx.recv().unwrap());
    let c = thread::current();
    println!("{}", c.name().unwrap());
    
}

pub fn main() {
    t2();
    function_name();
}
