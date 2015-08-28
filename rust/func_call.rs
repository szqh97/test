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

fn main() {
    let b = Baz;
    Foo::f(&b);
    Bar::f(&b);
}

