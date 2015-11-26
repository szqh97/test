use std::fmt;

#[derive(Copy, Clone)]
struct Info {
    value: i64,
}
struct Bob {
    name: String
}

impl Bob {
    fn new(name: &str) -> Bob {
        println!("new bob {:?}", name);
        Bob {name: name.to_string()}
    }
}

impl Drop for Bob {
    fn drop(&mut self) {
        println!("del bob {:?}", self.name);
    }
}

impl fmt::Debug for Bob {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "bob {:?}", self.name)
    }
}

fn black_home(bob:Bob) {
    println!("imminet shrinkage {:?}", bob);
}

fn main() {
    
    let b = Bob::new("A");
    black_home(b);
    black_home(b);

}
