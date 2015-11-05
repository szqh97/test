use std::env;

fn guess(n: i32) -> bool {
    if n < 1 || n > 10 {
        panic!("Invalid number: {}", n);
    }
    
    n == 5
}

fn arg_test() {

    let mut argv = env::args();
    let arg: String = argv.nth(1).unwrap();
    let n: i32 = arg.parse().unwrap();
    println!("{}", 2 * n);

}

fn find(haystack: &str, needle: char) -> Option<usize> {
    for (offset, c) in haystack.char_indices(){
        if c == needle{
            return Some(offset)
        }
    }
    None
    
}

fn extension(file_name: &str)->Option<&str> {
    find(file_name, '.').map(|i| &file_name[i+1..])
    
}

pub fn main() {
    //guess(11);
    
    //arg_test();
    
   let file_name = "foobar.rs";
   match find(file_name, '.'){
       None => println!("No file extension found."),
       Some(i) => println!("File extension:{}", &file_name[i+1..]),
   }

   println!("extension: {}", extension(file_name).unwrap());
   println!("extension: {}", extension("fooboar").unwrap_or("rs"));

}
