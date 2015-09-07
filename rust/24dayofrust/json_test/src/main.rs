extern crate rustc_serialize;

use rustc_serialize::Encodable;
use rustc_serialize::json::{self, Encoder};

#[derive(RustcEncodable)]
#[derive(Debug)]
struct User {
    name: String,
    post_count: u32,
    likes_burgers:bool,
    avatar: Option<Photo>,
}

#[derive(RustcEncodable)]
#[derive(Debug)]
struct Photo {
    url: String,
    dimensions: (u32,u32),
    
}

fn main() {

    println!("{}", json::encode(&42).unwrap() );
    println!("{}", json::encode(&vec!["to", "be", "or", "not", "to", "be"]).unwrap());
    println!("{}", json::encode(&Some(true)).unwrap());

    let user = User {
        name: "Zybszek".to_string(),
        post_count: 100u32,
        likes_burgers:true,
        avatar: Some(Photo{
            url: "http://baidy.com".to_string(),
            dimensions:(160u32, 100u32),
        }),
    };

    println!("{}", json::encode(&user).unwrap());

    let mut encoded = String::new();
    {
        let mut encoder = Encoder::new_pretty(&mut encoded);
        user.encode(&mut encoder).ok().expect("Json encode errror");
    }
    println!("{}", encoded);
}
