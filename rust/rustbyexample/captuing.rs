fn main() {
    let color = "green";
    let print = || println!("color {}", color.to_string());

    print();
    print();
    let mut count = 0;
    let mut inc = ||{
        count += 1;
        println!("Count is :{}", count);
    };
    inc();
    inc();

    let movable = Box::new(4);

    let consume = ||{
        println!("movable is {}", movable);
        drop(movable);
    };

    consume();
}
