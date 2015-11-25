#![feature(box_syntax)] 
struct Foo {
    f: Box<i32>,
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

}
