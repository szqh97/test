use std::cell::Cell;
struct Point {
    x: i32,
    y: Cell<i32>,
}

fn main() {
    let point = Point{x:5, y: Cell::new(6)};
    point.y.set(11);
    print!("y:{:?}", point.y);
    
}
