use std::sync::Arc;
use std::thread;
use std::time::Duration;

pub fn main() {
    let numbers: Vec<_> = (0..100u32).collect();
    let shared_numbers = Arc::new(numbers);

    for i in 0..10{
        let child_numbers = shared_numbers.clone();
        thread::spawn(move ||{
            let local_number = &child_numbers[..];
            println!("{}", local_number[i]);
            thread::sleep(Duration::new(15, 0))
        });
    }
}
