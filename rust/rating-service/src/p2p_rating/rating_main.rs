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
    let mut req_body = [0; 1024];
    let body_size = req.body.read(&mut req_body).unwrap() ;
    let mut str_body = String::new();
    if body_size != 0 {

        str_body = String::from_utf8(req_body.to_vec()).unwrap();
        println!("post body: {}", str_body.trim());
        let rating_req: RatingRequest = json::decode(&str_body).unwrap();
        println!("test post date : {}", rating_req.sample_post_date);
    }

    
    Response::with((status::Ok, ""))
}

pub fn p2p_rating_main() {
    Iron::new(|req: &mut Request|{
        println!("<<<<<< Request is : {:?}", req);

        //let mut body = [0;1024];
        //req.body.read(&mut body).unwrap();

        //println!("{}", String::from_utf8(body.to_vec()).unwrap());

        /*
        let body = req.get::<bodyparser::Raw>();
        println!("{:?}", body);
        */

        //println!("       Request body is : {:?}", req.body);
        Ok(match req.method {
            method::Get =>{
                Response::with((status::Ok, "test GET method"))

            },
            method::Post => {
                let resp = rating_post(req);
                //Response::with((status::Ok, "test POST method"))
                resp
            },
            _ => Response::with((status::BadRequest, "BadRequest"))
        })
    }).http("localhost:3000").unwrap();

}
