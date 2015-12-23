use std::mem;
use std::ptr;

fn main() {
    const SIZE: usize = 10;

    let mut x: [Box<u32>; SIZE];
    unsafe {
        x = mem::uninitialized();
        for e in x[..] {
            ptr::write(e, Box::new(11 as u32));
        }
    }
    println!("{:?}", x);
}
