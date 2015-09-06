fn print_one<'a>(x:&'a i32) {
    println!("print_one :x is {}", x);
}

fn add_one<'a>(x:&'a mut i32) {
    *x += 1;
}

fn print_multi<'a, 'b>(x: &'a i32, y:&'b i32) {
    println!("print_multi: x is {}, y is {}", x, y);
}

fn pass_x<'a, 'b>(x:&'a i32, _: &'b i32) -> &'a i32 {
    x
}

struct Owner(i32);

impl Owner {
    fn add_one<'a>(&'a mut self) {self.0 += 1}
    fn print<'a>(&'a self) {
        println!("print : {}", self.0);
    }
}
fn main() {
    let x = 7;
    let y = 9;
    print_one(&x);
    print_multi(&x, &y);

    let z = pass_x(&x, &y);
    print_one(z);

    let mut t = 3;
    add_one(&mut t);
    print_one(&t);


    let mut owner = Owner(11);
    owner.add_one();
    owner.print();
}
