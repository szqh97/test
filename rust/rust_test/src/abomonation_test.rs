#[macro_use]
extern crate abomonation;
use abomonation::{encode, decode, Abomonation};

#[derive(Eq, PartialEq)]
struct MyStruct {
    a: String,
    b: u64,
    c: Vec<u8>,
}

unsafe_abomonate!(MyStruct : a, b, c);

fn main() {

    // create some test data out of recently-abomonable types
    let my_struct = MyStruct { a: "grawwwwrr".to_owned(), b: 1, c: vec![1,2,3] };

    // encode a &MyStruct into a Vec<u8>
    let mut bytes = Vec::new();
    unsafe { encode(&my_struct, &mut bytes); }
    println!("{:?}", bytes);
    let mut bytes2 = [1, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 103, 114, 97, 119, 119, 119, 119, 114, 114, 1, 2, 3, 4];


    // decode a &MyStruct from &mut [u8] binary data
    if let Some((result, remaining)) = unsafe { decode::<MyStruct>(&mut bytes2) } {
        //assert!(result == &my_struct);
        //assert!(remaining.len() == 0);
        println!("{}, {}, {:?}", result.a, result.b, result.c);
        println!("result size{}", result.c.len());
        println!("remaining size {}", remaining.len());
    }
}
