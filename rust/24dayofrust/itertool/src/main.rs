#[macro_use]
extern crate itertools;
use itertools::Itertools;

fn main() {
//    println!("Hello, world!");
//
    let mut words = "hello supercallfrailisticexpialidocious programmer".split_whitespace();
    words.foreach(|word| println!("{} is {} characters long", word, word.len()));

    let even = (1..10).map(|x| x * 2);
    let odd = (1..5).map(|x| x * 2 + 1);
    println!("{:?}", even.interleave(odd).collect::<Vec<_>>());
}
