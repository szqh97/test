fn main(){

    let x:i32 = 44;
    println!("Hello, world");
    println!("the value is {}", x);
    print_number(add_ten(100));
    let a =[1,2,3,4,5];
    let mid = &a[1..3];
    let y: &i32;
    {
        let x = 5;
        y = &x;
    }
    //println!("{}", y);

}

fn print_number(x: i32) {
    for i in 100..x {
        println!("x is {}", i);
        
    }
    for (i,j) in (5..10).enumerate(){
        println!("i={} and j={}", j,j);
    }
    let _y = double(x);
    println!("{}", x);
    
}

fn double(x:i32) -> i32{
    x*2
}
fn add_ten(x: i32) ->  i32 {
    x+10
}

