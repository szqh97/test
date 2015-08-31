trait Foo {
    fn f (&self);
}

trait Bar{
    fn f (&self);
}

struct Baz;

impl Foo for Baz {
    fn f(&self) {
        println!("baz impl f" );
    }
}

impl Bar for Baz {
    fn f(&self) {
        println!("bar impl f" );
    }

}

macro_rules! foo {
    (x=> $e:expr) => (
        println!("mode X: {}", $e)
    );
    (y=> $e:expr) => (
        println!("mode y: {}", $e)
    );
}
macro_rules! five_time {
    ($x:expr) => (5*$x);
}
fn main() {
    let b = Baz;
    Foo::f(&b);
    Bar::f(&b);
    foo!(y=>3);
    foo!(x=>3);

    println!(five_time!(2 + 4));
}

