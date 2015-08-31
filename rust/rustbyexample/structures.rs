struct Nil;

struct Pair(i32, bool);

struct Point {
    x: f64,
    y: f64,
}

#[allow(dead_code)]
struct Rectangle {
    p1: Point,
    p2: Point,
}

fn main() {
    let point: Point = Point{x: 0.3, y: 0.5};
    println!("Point coordinates:({}, {})", point.x, point.y);

    let Point{x:my_x, y: my_y} = point;
    let _rectangle =  Rectangle{
        p1: Point{x:my_x, y: my_y},
        p2: point,
    };
    let _nil = Nil;
    let pair = Pair(1, false);

    let Pair(interger, decimal) = pair;
    println!("pair contains {:?} and {:?}", interger, decimal);



}
