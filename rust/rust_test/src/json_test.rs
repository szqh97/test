extern crate rustc_serialize;
use std::collections::BTreeMap;
use rustc_serialize::json::{self, Json, ToJson};



#[derive(RustcDecodable, RustcEncodable)]
pub struct TestStruct {
    data_int: u8,
    data_str: String,
    data_vector:Vec<u8>,
}

impl ToJson for TestStruct {
    fn to_json(&self) -> Json {
        let mut d = BTreeMap::new();

        d.insert("id".to_string(), self.data_int.to_json());
        d.insert("data_str".to_string(), self.data_str.to_json());
        d.insert("data_vector".to_string(), self.data_vector.to_json());

        Json::Object(d)
    }
}

pub fn main() {
    
    let obj = TestStruct {
        data_int: 1,
        data_str: "szqh97".to_string(),
        data_vector: vec![1;3],
    };

    let encoded = json::encode(&obj).unwrap();
    println!("encode : {}", encoded);

    let decoded:TestStruct  = json::decode(&encoded).unwrap();

    let json_obj: Json = obj.to_json();

    let json_str: String = json_obj.to_string();
    println!("{}", json_str);

}
