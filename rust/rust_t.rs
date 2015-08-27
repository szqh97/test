struct Circle {
    x: f64,
    y: f64,
    radius: f64,
}

impl Circle {
    fn area(&self) -> f64 {
        std::f64::consts::PI * (self.radius * self.radius)
    }

    fn grow(&self, increment: f64)->Circle {
        Circle{x: self.x, y:self.y, radius: self.radius + increment}
    }
}


struct CircleBuilder {
    x: f64,
    y: f64,
    radius: f64,
}

impl CircleBuilder {
    fn new()  -> CircleBuilder{
        CircleBuilder{x: 0.0, y: 0.0, radius: 1.0}
    }

    fn x(&mut self, coordinate: f64) -> &mut CircleBuilder {
        self.x = coordinate;
        self
    }

    fn y(&mut self, coordinate: f64) -> &mut CircleBuilder {
        self.y = coordinate;
        self
    }

    fn radius (&mut self, coordinate: f64) -> &mut CircleBuilder {
        self.radius = coordinate;
        self
    }
        
    fn finalize(&self) -> Circle {
        Circle {x: self.x, y: self.y, radius: self.radius}
        
    }
}

fn main() {
    let c = CircleBuilder::new().x(1.0).y(2.0).radius(4.0).finalize();

    println!("{}", c.area());
    let c = Circle{x: 0.0, y:0.0, radius: 2.0};
    println!("{}", c.area());
    let d = c.grow(9.0).area();
    println!("{}", d);
    let x = 18;
    match x {
        1 => println!("one"),
        2 => println!("two"),
        3 => println!("three"),
        4 => println!("four"),
        5 ... 9 => println!("pattern"),
        e @ 10 ... 20 => println!("got a element {}", e),
        _ => println!("something else"),

    }

    enum OptionalInt {
        Value(i32),
        Missing,
    }
    let x = OptionalInt::Value(59);

    match x {
        OptionalInt::Value(i) if i > 5 => println!("Got an int bigger than five!"),
        OptionalInt::Value(..) => println!("Got an int!"),
        OptionalInt::Missing => println!("No such luck."),
    }

   let x = 4;
   let y = false;
   match x {
       4 | 5 if y => println!("yes"),
       _ => println!("no"),
   }

   match x {
       ref r => println!("Got an ref to {}", r),
   }

   let v = vec![1,2,3,4,5,6];
   println!("The value is {}", v[3]);

   for i in v {
       println!("v is {}", i);
   }
    
   let mut v = vec![8,3,4,4,5,6,7];
   for i in &v {
       println!("in &v is {}", i);
   }

   for i in &mut v {
       //i = 8;
       println!("in &mut v is {}", i);
   }

   let hackiko ="上前大";
   for b in hackiko.as_bytes() {
       print!("{}, ", b);
   }
   println!("\n");

   for c in hackiko.chars() {
       print!("{},", c);
   }
   println!("\n");
       
}
