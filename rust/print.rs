use std::fmt;

#[derive(Debug)]
struct Structure(i32);

#[derive(Debug)]
struct Deep(Structure);

#[derive(Debug)]
struct MinMax(i64, i64);
impl fmt::Display for MinMax {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "({}, {})", self.0, self.1)
    }
}

#[derive(Debug)]
struct Point2{
    x: i64,
    y: i64,
}

impl fmt::Display for Point2 {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "x: {}, y: {}", self.x, self.y)
    }
}

impl fmt::Display for Structure {
    fn fmt (&self, f: &mut fmt::Formatter) -> fmt::Result{
        write!(f, "{}", self.0)
    }
}

struct List(Vec<i32>);

impl fmt::Display for List{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        let List(ref vec) = *self;
        let len = vec.len();
        
        for (count, v) in vec.iter().enumerate() {
            if count < len -1 {try!(write!(f, "{}, ", v))}
        }
        write!(f, "{}", vec[len-1])
    }
}

fn main() {
    println!("{}", Structure(9));
    println!("{:?} is print now", Structure(9));
    //println!("{:?} is print now", Deep(Structure(10)));
    //
    let m = MinMax(9,11);
    println!("{:?} is ", m);
    println!("{} is ", m);

    let p = Point2{x:3,y:5};
    println!("p is {:?}", p);
    println!("p is {}", p);

    let v = vec![1,2,3,4];
    println!("{:?}", v);

    println!("{}", List(v));
}
