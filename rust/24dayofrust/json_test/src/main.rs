extern crate rustc_serialize;

use rustc_serialize::Encodable;
use rustc_serialize::json::{self, Encoder};

#[derive(RustcEncodable, RustcDecodable)]
#[derive(Debug)]
struct User {
    name: String,
    post_count: u32,
    likes_burgers:bool,
    avatar: Option<Photo>,
}

#[derive(RustcEncodable, RustcDecodable)]
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
    
    let incoming_request = "{\"name\":\"John\",\"post_count\":2,\"likes_burgers\":false,\"avatar\":null}"; 
    let decoded: User = json::decode(incoming_request).unwrap();
    println!("My name is {} an I {} burgers", decoded.name, 
            if decoded.likes_burgers {"love"} else {"don't like "});
    assert!(decoded.avatar.is_none());

    let new_request = "{\"id\":64,\"title\":\"24days\",\"stats\":{\"pageviews\":1500}}";
    if let Ok(requset_json) = json::Json::from_str(new_request){
        if let Some(ref stats) = requset_json.find("stats"){
            if let Some(ref pageviews) = stats.find("pageviews"){
                println!("pageviews: {}", pageviews);
            }
        }
    }
}
