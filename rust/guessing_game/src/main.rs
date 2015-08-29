extern crate rand;
use std::io;
use rand::Rng;
use std::cmp::Ordering;

fn main() {
    let secret_number = rand::thread_rng().gen_range(1, 10);
    loop {
        println!("Guessing the number!");
        println!("Please input your guess.");
        let mut guess = String::new();
        io::stdin().read_line(&mut guess)
            .ok()
            .expect("Failed to read line");
        println!("You guessted {}", guess);
        //let guess: u32 = guess.trim().parse()
        //    .ok()
        //    .expect("please type a number");
        let guess: i32 = match guess.trim().parse(){
            Ok(num) => num,
            Err(_) => continue,
        };
        println!("Yougess {}", guess);
        match guess.cmp(&secret_number) {
            Ordering::Less  => println!("Too Small!"),
            Ordering::Greater => println!("Too big!"),
            Ordering::Equal => {
                println!("You win!");
                break
            }
        }


    }
}
