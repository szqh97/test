
#![feature(box_syntax)] 
struct Foo {
    f: Box<i32>,
}

#[warn(dead_code)] 
fn max<'a>(x: &'a Foo, y: &'a Foo)-> &'a Foo {
    if x.f > y.f { x } else { y }
}

#[warn(dead_code)] 
struct Link<'a> {
    link: &'a Foo,
}

#[warn(dead_code)] 
fn store_foo<'a>(x:&mut Link<'a>, y:&'a Foo) {
 //   x.link = y;
 //
    
}

fn main() {
    /*
     * #1 
    let mut a = Foo{f: box 0};
    //let x = &mut a;
    // cannot borrow a.f as immutable because a is also borrowed as x
    //println!("{}", a.f);
    //
    */

    /*
     *
    let mut a = Foo{f: box 0};

    {

        let x = &mut a;
    }
    println!("{}", a.f);
    */

    /*
    let mut a = Foo {f: box 0};
    let x = &mut a;
    let y = x;

    // error 
    //println!("{}", x.f);
    */


    /*
    let mut a = Foo {f: box 0};
    let y: &Foo;
    if false {
        let x = &a;
        y = x;
    }

    a.f = box 1;
    */


    /*
    let a = Foo { f: box 1 };
    let y: &Foo;

    if false {
        let b = Foo {f: box 0};
        let x = max(&a, &b);
    }
    //y = x;
    */

    /*
    let a = Foo {f: box 0};
    let mut x = Link{link: &a};

    if true{
        let b = Foo {f: box 1};
        let i = 1/0;
        println!("{}", i);

    }
    */

    /*
    let a = Foo {f: box 0};
    let x = &mut  Link{link: &a};
    if true {
    let b = Foo {f: box 1};
    store_foo(x, &b);
    }
    */


}
