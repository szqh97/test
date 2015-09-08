//extern crate uuid;
extern crate uuid;
use uuid::Uuid;
fn main() {
    println!("Hello, world!");
    for _ in 0..1000{
        //println!("{}", Uuid::new_v4().to_hyphenated_string());
        let u = Uuid::new_v4();
        println!("{}", u.to_string());
        println!("{}", u.to_hyphenated_string());
    }
}
