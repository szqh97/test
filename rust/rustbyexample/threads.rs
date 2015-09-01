use std::thread;
static NTHREADS:u32 = 100;
fn main() {
    let mut children = vec![];
    
    for i in 0..NTHREADS {
        children.push(thread::spawn(move||{
            println!("thisi is thread number: {}", i)
        }));
    }

    for child  in children {
        let _ = child.join();
    }
}
