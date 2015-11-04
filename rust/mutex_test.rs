use std::sync::{Arc, Mutex};
use std::thread;
use std::sync::mpsc::channel;
use std::time::Duration;

pub fn main() {
    const N: usize = 10;
    let data = Arc::new(Mutex::new(0));

    let (tx, rx) = channel();
    for _ in 0..10{
        let (data, tx) = (data.clone(), tx.clone());
        thread::spawn(move||{
            let mut data = data.lock().unwrap();
            thread::sleep(Duration::new(0,5000));
            *data += 1;
            if *data > 3 {
                tx.send(*data).unwrap();
            }
        });
    }

    while true {
        let x = rx.recv().unwrap();
        println!("{}", x);
    }

}
