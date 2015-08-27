struct Foo<'a> {
    x: &'a  i32,
}

fn main() {
    let x:&i32 = &7;
    {
        let y = &5;
        let f = Foo {x:y};
        //x = &f.x;
        //k = f.x;
    }
    println!("{}", x);
    
}
