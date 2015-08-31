macro_rules! say_hello {
    () => (
        println!("Hello");
    );
}
macro_rules! create_function {
    ($fun_name: ident) => (
        fn $fun_name() {
            println!("You called {:?}()", stringify!($fun_name));
        }
    );
}
create_function!(foo);
create_function!(bar);

macro_rules! print_result {
    ($expression: expr) => (
        println!("{:?} + {:?}", stringify!($expression), $expression);
    );
}
macro_rules! test {
    ($left:expr; and $right:expr) => (
        println!("{:?} and {:?} is {:?}", 
                stringify!($left),
                stringify!($right),
                $left && $right);
    );
    ($left:expr; or $right:expr) =>(
        println!("{:?} or {:?} is {:?}",
                stringify!($left),
                stringify!($right),
                $left || $right);
    );
}

macro_rules! min {
    ($x:expr) => (
        $x
    );
    ($x:expr, $($y:expr), +)=>(
        std::cmp::min($x, min!($($y), +))
  );
}
fn main() {
    say_hello!();
    foo();
    bar();
    print_result!(1u32 + 1);
    print_result!({
        let x = 1u32;
        x*x +2*x -1
    });

    test!(true; or false);
    test!(true; and false);

    test!(1i32 +1 == 2i32; and 2i32 * 2 == 4i32);
    
    println!("{}", min!(1u32));
    println!("{}", min!(1u32, 2u32+2));
    println!("{}", min!(5u32, 2u32 + 3, 4u32));


    
}
