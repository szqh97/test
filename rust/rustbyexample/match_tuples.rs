fn main() {
    let pair = (1, -2);
    println!("Tell me about {:?}", pair);

    match pair {
        (0, y) => println!("First is 0, and second is {:?}", y),
        (x, 0) => println!("Second is 0, and first is {:?}", x),
        _      => println!("It doesn't matter what they are"),
    }
}
