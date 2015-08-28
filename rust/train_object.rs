trait Foo {
    fn method(&self) -> String;
}

impl Foo for u8 {
    fn method(&self) -> String {
        format!("u8: {}", *self)
    }
}
impl Foo for String {
    fn method(&self) -> String {
        format!("String: {}", *self)
    }
}

//fn do_something<T: Foo> (x: T) {
//   println!("{}", x.method());
//}

fn do_something(x: &Foo) {
    println!("{}", x.method());
}




fn main() {
    let x = 5u8;
    let y = "Hello".to_string();
    do_something(&x as &Foo);
    do_something(&y);
    let plus_one = |x: i32| x + 1;
    println!("{}", plus_one(10));

    let mut num = 5;
    let pus_num = |x: i32| x + num;
    let y = &num;
    println!("{}", y);

    let mut num = 5;
    {
        let mut add_num = move |x: i32| num += x;
        add_num(5);
    }
    println!("{}", num);

    let mut num = 5;
    {
        let mut add_num = |x: i32| num += x;
        add_num(5);
    }
    println!("{}", num);
}
