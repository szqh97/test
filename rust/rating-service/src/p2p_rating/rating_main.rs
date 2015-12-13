extern crate iron;
extern crate bodyparser;
use std::io;
use std::io::prelude::*;
use iron::prelude::*;
use iron::{status, method};

use super::rating_types;
use super::rating_types::{RatingRequest};
use std::collections::BTreeMap;
use rustc_serialize::json::{self, Json, ToJson};



fn rating_post(req: &mut Request) -> Response {
    // FIXME body_buffer may in heap..
    let mut body_buffer = [0; 1024];

    let body_size = req.body.read(&mut body_buffer).unwrap() ;
    let (left, _) = body_buffer.split_at_mut(body_size);
    let mut str_body = String::new();

    if body_size != 0 {
        str_body = String::from_utf8(left.to_vec()).unwrap();
        println!("post body: {}", str_body.trim());
        let rating_req: RatingRequest = json::decode(&str_body).unwrap();

    }

    Response::with((status::Ok, ""))
}

pub fn p2p_rating_main() {
    Iron::new(|req: &mut Request|{
        println!("<<<<<< Request is : {:?}", req);

        /*
        let body = req.get::<bodyparser::Raw>();
        */

        Ok(match req.method {
            method::Get =>{
                Response::with((status::Ok, "test GET method"))
            },
            method::Post => {
                rating_post(req)
            },
            _ => Response::with((status::BadRequest, "BadRequest"))
        })
    }).http("localhost:3000").unwrap();

}
