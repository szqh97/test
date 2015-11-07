use std::fs::File;
use std::io::Read;
use std::path::Path;
use std::io;
use std::num;
use std::fmt::{Debug, Display};
use std::fmt;
use std::error;

fn file_double<P: AsRef<Path>>(file_path: P) -> usize {
    let mut file = File::open(file_path).unwrap();
    let mut contents = String::new();
    
    let n = file.read_to_string(&mut contents).unwrap();
    2*n
}

fn file_double2<P: AsRef<Path>> (file_path: P) -> Result<i32, String> {
    File::open(file_path)
        .map_err(|err| err.to_string())
        .and_then(|mut file| {
            let mut contens = String::new();
            file.read_to_string(&mut contens)
                .map_err(|err| err.to_string())
                .map(|_| contens)
        })
        .and_then(|contens| {
            contens.trim().parse::<i32>()
                   .map_err(|err| err.to_string())
        })
        .map(|n| 2*n)
}

/*
fn file_length_double<P: AsRef<Path>> (file_path: P) -> Result<i32, String> {
    File::open(file_path)
        .map_err(|err| err.to_string())
        .and_then(|mut file|{
            let mut contents = String::new();
            file.read_to_string(&mut contents)
                .map_err(|err| err.to_string())
                .map(|_| contents)
        })
        .and_then(|contents|{
            contents.len()
        })
    
}

*/

fn file_double3<P: AsRef<Path>>(file_path: P) -> Result<i32, String> {
    let mut file = match File::open(file_path){
        Ok(file) => file,
        Err(err) => return Err(err.to_string()),
    };
    let mut contents = String::new();
    if let Err(err) = file.read_to_string(&mut contents){
        return Err(err.to_string());
    }
    let n: i32 = match contents.trim().parse(){
        Ok(n) => n,
        Err(err) => return Err(err.to_string()),
    };
    Ok(2*n)
}

fn file_double4<P: AsRef<Path>>(file_path: P) -> Result<i32, String> {
    let mut file = try!(File::open(file_path).map_err(|e| e.to_string()));
    let mut contents = String::new();
    try!(file.read_to_string(&mut contents).map_err(|e| e.to_string()));
    let n = try!(contents.trim().parse::<i32>().map_err(|e| e.to_string()));
    Ok(2*n)
    
}


#[derive(Debug)]
enum CliErr {
    Io(io::Error),
    Parse(num::ParseIntError),
}

impl fmt::Display for CliErr{
    fn fmt(&self, f: &mut fmt::Formatter)-> fmt::Result {
        match *self {
            CliErr::Io(ref err) => write!(f, "IO error: {}", err),
            CliErr::Parse(ref err) => write!(f, "Parse error: {}", err),
        }
    }
}
impl error::Error for CliErr {
    fn description(&self) -> &str {
        match *self {
            CliErr::Io(ref err) => err.description(),
            CliErr::Parse(ref err) => error::Error::description(err),
        }
    }

    fn cause(&self) -> Option<&error::Error> {
        match *self {
            CliErr::Io(ref err) => Some(err),
            CliErr::Parse(ref err) => Some(err),
        }
    }
}


fn file_double5<P: AsRef<Path>>(file_path:P) -> Result<i32, CliErr> {
    let mut file = try!(File::open(file_path).map_err(CliErr::Io));
    let mut contents = String::new();
    try!(file.read_to_string(&mut contents).map_err(CliErr::Io));
    let n = try!(contents.trim().parse::<i32>().map_err(CliErr::Parse));
    Ok(2*n)
}

fn file_double6<P: AsRef<Path>>(file_path: P) -> Result<i32, Box<error::Error>> {
    let mut file = try!(File::open(file_path));
    let mut contents = String::new();
    try!(file.read_to_string(&mut contents));
    let n = try!(contents.trim().parse::<i32>());
    Ok(2*n)
    
}

pub fn main() {
    let doubled = file_double("./file_op.rs");
    println!("doubled {}", doubled);

    println!("{}", file_double2("foobar").unwrap());
    println!("{}", file_double3("foobar").unwrap());
    println!("{}", file_double4("foobar").unwrap());

    match file_double5("foobar.rs") {
        Ok(n) => println!("{}", n),
        Err(err) => println!("{:?}", err),
    }
    println!("{:?}", file_double6("foobar").unwrap());
}
