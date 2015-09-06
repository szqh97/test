use std::mem;

#[allow(dead_code)]
#[derive(Debug)]

struct Point {
    x: f64,
    y: f64,
}

#[allow(dead_code)]
struct Rectangle {
    p1: Point,
    p2: Point,
}

fn origin() -> Point {
    Point {x:0.0, y:0.0}
}

fn boxed_orgin() -> Box<Point> {
    Box::new(Point{x: 0.0, y: 0.0})
}

fn main() {
    let point: Point = origin();
    let rectangel: Rectangle = Rectangle{
        p1: origin(),
        p2: Point{x:3.0, y:4.0},
    };

    let boxed_rectangle: Box<Rectangle> = Box::new(Rectangle{
        p1: origin(),
        p2: origin(),
    });

    let boxed_point: Box<Point> = Box::new(origin());

    let box_in_a_box: Box<Box<Point>> = Box::new(boxed_orgin());

    println!("Point occuples {} bytes in the stack", mem::size_of_val(&point));
    println!("rectangel occuples {} bytes in the stack", mem::size_of_val(&rectangel));
    println!("boxed_rectangle occuples {} bytes in the stack", mem::size_of_val(&boxed_rectangle));
    println!("box_in_a_box occuples {} bytes in the stack", mem::size_of_val(&box_in_a_box));


}
