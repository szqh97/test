extern crate zookeeper;

use std::collections::HashMap;
use std::sync::mpsc;
use zookeeper::listeners;

pub fn listeners_test() {
    let (tx1, rx1) = mpsc::channel();
    let (tx2, rx2) = mpsc::channel();
    let ls = listeners::ListenerSet::<i32>::new();
    println!("ls length is {}", ls.len());
    let s1 = ls.subscribe(tx1);
    let s2 = ls.subscribe(tx2);
    println!("ls length is {}", ls.len());

    ls.notify(&11);
    println!("rx1 recv: {}",rx1.recv().unwrap());
    println!("rx2 recv: {}",rx2.recv().unwrap());
    /*
    let listenersMap= (*ls.listeners).lock().unwrap();
    for iter in listenersMap.iter(){
        if listenersMap.
        println!("{:?}", iter.0);
    }
    */
    ls.unsubscribe(s2);
    ls.notify(&13);
    println!("rx1 recv: {}",rx1.recv().unwrap());

    
}
pub fn main() {
    listeners_test();
    
}
