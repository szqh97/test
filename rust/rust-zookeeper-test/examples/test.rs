extern crate zookeeper;

#[macro_use]
extern crate log;
extern crate env_logger;

use zookeeper::consts::*;
use std::collections::HashMap;
use std::sync::mpsc;
use zookeeper::listeners;

use zookeeper::watch;
use zookeeper::{Watcher, WatchedEvent};

use zookeeper::io;
use zookeeper::{RawResponse, RawRequest};
//use zookeeper::{io, RawResponse};
use std::thread;
use std::io::Cursor;

use zookeeper::proto::{ReadFrom, ReplyHeader, ByteBuf};
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
    println!("xxxxxxxxxxxxxxxxxxxxxxx");
    let mut s = String::from("foo");

    let chroot  = Some(s);
    let mut zkw = watch::ZkWatch::new(LoggingWatcher, chroot);
    let sender = zkw.sender();
    thread::spawn(move ||{
        let header = ReplyHeader{xid:0, zxid: 0, err: ZkError::ConnectionLoss as i32};
        let data = Cursor::new(b"tedfsfsdfsfdsst\n\r\r\n".to_vec());
        let resp = RawResponse{header:header, data:data };
        sender.send(watch::WatchMessage(resp));
    });

    //zkw.run();
    /* 
     * read from string
    let mut data = Cursor::new(b"tedfsfsdfsfdsst\n\r\r\n".to_vec());
    
    let header = match ReplyHeader::read_from(&mut data){
        Ok(header) => header,
        Err(e) => {
            println!("failed to construct header {:?}", data);
            println!("err: {:?}", e.to_string());
            return
        }
    };
    println!("xid: {:?}", header.xid);
    */
 //   let response = RawResponse{header: header, data: ByteBuf::new(vec![])};

    

    
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
    //test_io();
    test_watch();

}
