use std::io::prelude::*;
use std::io::{self,Result, SeekFrom};
use std::fs::File;

fn write_ten_bytes_at_end<W: Write + Seek>(writer: &mut W) -> Result<()> {
    try!(writer.seek(SeekFrom::End(-10)));
    for i in 0..10{
        try!(writer.write(&[i]));
    }
    Ok(())
}

pub fn main() {
    let mut file = try!(File::create("foo.txt").map_err(|e| e.to_string()));
    //try!(write_ten_bytes_at_end(&mut file));
    
}
