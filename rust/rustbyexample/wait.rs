use std::process::Command;
fn main() {
    let _process = Command::new("sleep").arg("5").spawn();
    println!("Reached end of main");
}
