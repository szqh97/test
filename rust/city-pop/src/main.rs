extern crate getopts;
extern crate rustc_serialize;
extern crate csv;

use std::path;
use getopts::Options;
use std::env;
use std::fs::File;
use std::error::Error;

#[derive(Debug, RustcDecodable)]
struct Row {
    country: String, 
    city: String,
    accent_city: String,
    region: String,
    
    population: Option<u64>,
    latitude: Option<f64>,
    longitude: Option<f64>,
}

struct PopulationCount {
    city: String,
    country: String,
    count: u64,
}

fn print_usage(program: &str, opts: Options) {
    println!("{}", opts.usage(&format!("Usage: {} [options] <data-path> <city>", program)));
}

fn searech<P: AsRef<path::Path>>(file_path: P, city: &str) -> Vec<PopulationCount> {
    let mut found = vec![];
    let file = File::open(file_path).unwrap();
    let mut rdr = csv::Reader::from_reader(file);
    for row in rdr.decode::<Row>() {
        let row = row.unwrap();
        match row.population {
            None => {},
            Some(count) => if row.city == city {
                found.push(PopulationCount{
                    city: row.city,
                    country:row.country,
                    count: count,
                });
            },
        };
    }

    found
    
}

fn search2<P: AsRef<path::Path>>(file_path: P, city: &str) -> Result<Vec<PopulationCount>, Box<Error + Send + Sync>> {
    let mut found = vec![];
    let file = try!(File::open(file_path));
    let mut rdr = csv::Reader::from_reader(file);
    for row in rdr.decode::<Row>(){
        let row = try!(row);
        match row.population  {
            None => {},
            Some(count) => if row.city == city{
                found.push(PopulationCount{
                    city: row.city,
                    country: row.country,
                    count: count,
                });
            },
        };
    }
    if found.is_empty(){
        Err(From::from("No matching cities with a population were found"))
    }else{
        Ok(found)
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    let program = args[0].clone();
    
    let mut opts = Options::new();
    opts.optopt("f", "file", "Choose an input file, instead of using STDIN", "NAME");
    opts.optflag("h", "help", "Show this usage message.");

    if args.len() <= 1 {
        print_usage(&program, opts);
        return;
    }

    let matches = match opts.parse(&args[1..]){
        Ok(m) =>{m}
        Err(e) => {panic!(e.to_string())}
    };

    if matches.opt_present("h"){
        print_usage(&program, opts);
        return;
    }

    let file = mtches.opt_str("f");
    let  data_flle = file.as_ref().map(path::Path::new);

    /* 

    let data_file = args[1].clone();
    let data_path = path::Path::new(&data_file);
    let city = args[2].clone();

     * version 1
     *
     *
    let file =File::open(data_path).unwrap();
    let mut rdr = csv::Reader::from_reader(file);

    for row in rdr.decode::<Row>() {
        let row = row.unwrap();
        
        if row.city == city {
            println!("{}, {}: {:?}", 
                    row.city, row.country, 
                    row.population.expect("population count"));
        }
    }

    */


    for pop in searech(&data_path, &city) {
        println!("{}, {}: {:?}", pop.city, pop.country, pop.count);
    }

    for pop in search2(&data_path, &city).unwrap() {
        println!("{:?}", pop.city);
    }

}
