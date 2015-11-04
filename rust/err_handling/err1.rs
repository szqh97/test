use std::env;

fn guess(n: i32) -> bool {
    if n < 1 || n > 10 {
        panic!("Invalid number: {}", n);
    }
    
    n == 5
}

pub fn main() {
    //guess(11);
    
    let mut argv = env::args();
    let arg: String = argv.nth(1).unwrap();
    let n: i32 = arg.parse().unwrap();
    println!("{}", 2 * n);


}
