extern crate csv;
extern crate rustc_serialize;
use csv::Writer;
use std::path::Path;

#[derive(Debug)]
#[derive(RustcEncodable)]
struct Movie {
    title:String,
    bad_guy:String,
    pub_year:usize,
}

fn main() {
    /* println!("Hello, world!");*/
    let dollar_films = vec![
        ("A Fistful of Dollars", "Rojo", 1964),
        ("For a few Dollars More", "El Indio", 1965),
        ("the Good, the Bad and the Ugly", "Tuco", 1966),
    ];
    let path = "western.csv";
    let mut writer = Writer::from_file(path).unwrap();
    for row in dollar_films{
        writer.encode(row).ok().expect("CSV writer error");
    }

    let movie = Movie{
        title: "Implos".to_string(),
        bad_guy: "Joe".to_string(),
        pub_year: 1999,
    };
    writer.encode(movie).ok().expect("CSV writer error");

    //let mut reader = csv::Reader::from_file(path).unwrap();
    let p = Path::new("/home/li_yun/Projects/test/rust/24dayofrust/csv_test/western.csv");
    let mut reader = csv::Reader::from_file(p).unwrap();
    println!("has headers: {}", reader.has_headers);
    for row in reader.decode(){
        println!("xx");
        let row:(String, String, usize) = row.unwrap();
        println!("{:?}", row);
    }

    println!("{:?}, {:?}, {:?}", p.file_name(), p.extension(), p.parent());


    let data ="
sticker,mortals,7
bribed,personae,7
wobbling,poncing,4
interposed,emmett,9
chocolate,refile,7";

    let mut rdr = csv::Reader::from_string(data).has_headers(false);
    for row in rdr.decode(){
        let (n1, n2, n3):(String, String, i8) = row.unwrap();
        println!("=>{}, {}:{}", n1, n2,n3);
    }
}
