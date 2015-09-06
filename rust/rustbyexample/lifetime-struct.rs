#[derive(Debug)]
struct Borrowed<'a> (&'a i32);

#[derive(Debug)]
struct NamedBorrowed<'a> {
    x: &'a i32,
    y: &'a i32,
}

#[derive(Debug)]
enum Ether<'a> {
    Num(i32),
    Ref(&'a i32),
}

fn main() {
    let x= 10;
    let y = 16;
    let single= Borrowed(&x);
    let double = NamedBorrowed{x:&x, y:&y};
    let reference = Ether::Ref(&x);
    let number = Ether::Num(y);
    
    println!("x is Borrowed in {:?}", single);
    println!("x and y are Borrowed in {:?}", double);
    println!("x is Borrowed in {:?}", reference);
    println!("y is *not* Borrowed in {:?}", number);
}

