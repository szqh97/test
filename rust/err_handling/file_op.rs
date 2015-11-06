use std::fs::File;
use std::io::Read;
use std::path::Path;

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

pub fn main() {
    let doubled = file_double("./file_op.rs");
    println!("doubled {}", doubled);

    println!("{}", file_double2("foobar").unwrap());
}
