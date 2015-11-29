use std::thread;
use std::time::Duration;
use std::sync::Arc;
use std::sync::Mutex;
use std::sync::mpsc;

fn channel_test() {
   let data = Arc::new(Mutex::new(0));

   let (tx, rx) = mpsc::channel();

   for _ in 0..10 {
       let (data, tx) = (data.clone(), tx.clone());

       thread::spawn(move || {
           let mut data = data.lock().unwrap();
           *data += 1;
           tx.send(());
       });
   }

   for _ in 0..10 {
       rx.recv();
   }
   println!("{:?}", Some(data));
}


fn main() {
    //thread_test();
    channel_test();
    let mut s = [1,2,2,3,4,5];
    println!("{:?}", &s[2..2+2]);
    
}
