extern crate hyper;
extern crate url;
use url::form_urlencoded;
use std::io::Read;
use hyper::{Client};



fn get_content(url: &str)-> hyper::Result<String> {
    let client = Client::new();
    let mut response = try!(client.get(url).send());
    let mut buf = String::new();
    try!(response.read_to_string(&mut buf));
    Ok(buf)

    
}

type Query<'a> = Vec<(&'a str, &'a str)>;

fn post_query(url: &str, query:Query) -> hyper::Result<String> {
    let client = Client::new();
    let body = form_urlencoded::serialize(query);
    let mut response = try!(client.post(url).body(&body[..]).send());
    let mut buf = String::new();
    try!(response.read_to_string(&mut buf));
    Ok(buf);
}

fn main() {
    /*
    let client = Client::new();
    let url = "http://www.baidu.com";
    let mut response = match client.get(url).send() {
        Ok(response) => response,
        Err(_) => panic!("Broke up"),
    };
    let mut buf = String::new();
    match response.read_to_string(&mut buf) {
        Ok(_) => (),
        Err(_) => panic!("I gave up"),
    };
    println!("buf: {}", buf);
    */
    println!("buf: {:?}", get_content("http://www.baidu.com"));
}


