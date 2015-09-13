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
    println!("{:?}", Uuid::parse_str("d27cdb6e-ae6d-11cf-96b8-44455354000"));
    println!("{:?}", Uuid::parse_str("x27cdb6e-ae6d-11cf-96b8-444553540000"));
    println!("{:?}", Uuid::parse_str("d27cdb6-eae6d-11cf-96b8-444553540000"));
    println!("{:?}", Uuid::parse_str("d27cdb6e-ae6d-11cf-96b8-444553540000"));
}
