extern crate image;
use std::fs::File;

fn main() {
    println!("Hello, world!");
    let img = image::open("/home/szqh97/Pictures/err.png").ok().expect("Opening image failed");
    let filterd = img.fliph();
    let mut out = File::create("out.png").unwrap();
    let _ = filterd.save(&mut out, image::PNG).ok().expect("saving image failed");
}
