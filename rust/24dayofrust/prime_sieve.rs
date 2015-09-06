extern crate primal;
use primal::Sieve;

fn main() {
    let sieve =  Sieve::new(10000);
    let suspect = 5273;
    println!("{} is prime:{}", suspect, sieve.is_prime(suspect));
    let not_prime = 1024;
    println!("{} is prime:{}", not_prime, sieve.is_prime(not_prime));


}
