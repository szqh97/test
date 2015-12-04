extern crate rustc_serialize;
extern crate chrono;
use std::collections::BTreeMap;
use rustc_serialize::json::{self, Json, ToJson};

//use chrono::{DateTime, Local};


#[derive(RustcDecodable)]
struct RatingRequest {
   sample_title             : String,
   //sample_post_date         : DateTime<Local>,
   sample_post_date         : String,
   peers                    : i32,
   meta_title               : Vec<String>,
   //meta_post_date           : Vec<DateTime<Local>>,
   meta_post_date           : Vec<String>,
}

impl ToJson for RatingRequest {
    fn to_json(&self) -> Json {
        let mut d = BTreeMap::new();
        d.insert("sample_title".to_string(), self.sample_title.to_json());
        d.insert("sample_post_date".to_string(), self.sample_post_date.to_json());
        d.insert("peers".to_string(), self.peers.to_json());
        d.insert("meta_title".to_string(), self.meta_title.to_json());
        d.insert("meta_post_date".to_string(), self.meta_post_date.to_json());
        Json::Object(d)
        
    }
}

#[derive(RustcDecodable)]
struct RatingResponse {
    err_code                : i32,
    err_msg                 : String,
    rating_score            : u32,
}

impl ToJson for RatingResponse {
    fn to_json(&self) -> Json {
        let mut d = BTreeMap::new();
        d.insert("err_code".to_string(), self.err_code.to_json());
        d.insert("err_msg".to_string(), self.err_msg.to_json());
        d.insert("rating_score".to_string(), self.rating_score.to_json());

        Json::Object(d)
    }
}



#[test]
pub fn test_ratingrequest_encode() {
    let req: RatingRequest = RatingRequest {
        sample_title: "Teen Wolf".to_string(),
        sample_post_date: "2015-01-01".to_string(),
        peers: 19,
        meta_title: vec!("Teen Wolf S1".to_string(), "Teen Wolf S2".to_string()),
        meta_post_date: vec!("2013-11-12".to_string(), "2014-11-12".to_string())
    };

    let json_obj: Json = req.to_json();
    let json_str: String = json_obj.to_string();
    println!("rating request: {}", json_str);

    let req: RatingRequest = json::decode(&json_str).unwrap();
    println!("{:?}", req.meta_title);
}

#[test]
pub fn test_ratingresponse_encode() {
    let resp: RatingResponse = RatingResponse {
        err_code: 0,
        err_msg: "rating successful".to_string(),
        rating_score: 145,
    };
    let json_str: String = resp.to_json().to_string();
    println!(" rating response: {}", json_str);
}
