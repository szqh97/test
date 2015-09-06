use std::fmt::Debug;
#[derive(Debug)]

struct Ref<'a, T: 'a>(&'a T); 

fn print<T>(t: T) where T:Debug {
    println!("print: t is {:?}", t);
}

fn print_ref<'a, T>( t:&'a T) 
    where T: Debug + 'a {
    println!("print_ref: t is {:?}", t);
}

fn coecre_first<'a: 'b, 'b>(x:&'a i32, _:&'b i32) ->&'b i32 {
    x
}

fn b<'a>(x:&'a i32, _:&'a i32) -> &'a i32{
    x
}

static NUM:i32 = 18;
fn coerced_static<'a>(_:&'a i32) -> &'a i32{
    &NUM
}


fn main() {
    let x = 7;
    let ref_x = Ref(&x);

    print_ref(&ref_x);
    print(ref_x);

    let x = 800;
    let y = 8;
    let borrow_big = &x;

    {
        let borrow_small = &y;
        let coerced = coecre_first(borrow_big, borrow_small);
        println!("coerced is {}", coerced);
        println!(" b is {:?}", b(borrow_big, borrow_small));
    }

    {
        let static_string = "In Read-only Memory";
        println!("staic string holds:{}", static_string);
    }

    println!("but now it's gone");
    println!("NUM: {} is still around though!", NUM);

    {
        let i = 9;
        let coerce_num = coerced_static(&i);
        println!(" coerce_num: {}", coerce_num);

    }
}
