struct Foo<'a> {
    vec1: Vec<i32>,
    slice: &'a mut [i32],
}

impl<'a> Foo<'a>{
    fn new(slice: &'a mut [i32]) -> Foo<'a> {
        Foo {vec1: vec!(1;10), slice: slice}
    }
    
}

fn echo<'a> (s: &'a str) -> &'a str {
    s
}


struct A {
    data: i32,
}

impl A {
    pub fn new() -> A{
        A {data: 0}
    }
    fn member_func<'a>(&'a self)-> B {
        B::new(self)
    }
}

struct B {
    data: i32,
}

impl B {
    pub fn new(a: &A) -> B {
        B{data:a.data+1 }
    }
}

fn main() {
    let mut arr = [1, 2, 3,];
    let foo = Foo::new(&mut arr);

    let ss = echo("xxxx");
    println!("{:?}", ss);

    let mut mut_a = A::new();
    let b = mut_a.member_func();
    mut_a.data+=1;

    println!("{:?}", b.data);

}
