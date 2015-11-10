extern crate zookeeper;

use std::collections::HashMap;
use std::sync::mpsc;
use zookeeper::listeners;

use zookeeper::watch;
use zookeeper::{Watcher, WatchedEvent};

use zookeeper::io;

pub fn test_io() {
    let (addrs, chroot) = zookeeper::ZooKeeper::parse_connect_string("127.0.0.1:2181, ::1:2181/mesos").unwrap();
    println!("length {}", addrs.len());
    println!("{:?}", addrs);
    println!("{:?}", chroot);
    let mut hosts = zookeeper::io::Hosts::new(addrs);
    let addr = hosts.get();
    println!("{:?}", addr);
    
}

struct LoggingWatcher;
impl Watcher for LoggingWatcher {
    fn handle(&mut self, e: &WatchedEvent) {
        //info!("{:?}", e)
        println!("{:?}", e)
    }
}

pub fn test_watch() {
    let chroot = "mesos";
    let zkw = watch::ZkWatch::new(chroot, LoggingWatcher);
    
}

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
    //listeners_test();
    test_io();
    
}
