extern crate iron;
extern crate rating_main;

use iron::prelude::*;
use iron::{status, method};
use rating_service::rating_main::{p2p_rating_main};

fn main() {
    p2p_rating_main();
    /*
    Iron::new(|req: &mut Request|{
        println!("<<<<<< Request is : {:?}", req);
        //Ok(Response::with((status::Ok, "hello_world!")))
        Ok(match req.method {
            method::Get =>{
                resp = Response::with((status::Ok, "test GET method"))

            },
            method::Post => {
                Response::with((status::Ok, "test POST method"))
            },
            _ => Response::with((status::BadRequest, "BadRequest"))
        })
    }).http("localhost:3000").unwrap();
    */
    
}
