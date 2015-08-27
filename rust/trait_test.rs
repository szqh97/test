impl HasArAea for Circle {
    fn area(&self) -> f64 {
        std::f64::consts::PI * self.radius * self.radius
    }
}

struct Circle {
    x: f64,
    y: f64,
    radius: f64,
}

trait HasArAea {
    fn area(&self) -> f64;
}



struct Square {
    x: f64,
    y: f64,
    side: f64,
}


impl HasArAea for Square {
    fn area (&self) -> f64 {
        self.side * self.side
    }
}

impl HasArAea for i32 {
    fn area(&self) -> f64 {
        println!("this is silly!");
        *self as f64
    }
}

fn print_area<T: HasArAea>(shape: T) {
    println!("The shape has a area of {}", shape.area());
}

fn main() {
    let c = Circle{x: 1.0, y:1.0, radius: 3.0};
    let s = Square{x: 0.0, y: 0.0, side: 9.0};
    print_area(c);
    print_area(s);

    print_area(55);
    5.area();
    
}
