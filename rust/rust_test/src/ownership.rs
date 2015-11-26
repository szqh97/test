use std::fmt;
use std::rc::Rc;
use std::cell::RefCell;
use std::thread;

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

fn black_home(mut bob: Bob) {
    println!("imminet shrinkage {:?}", bob);
}

fn mutabe(mut value: Bob) {
    value.name = "mutata".to_string();
}

fn black_hole<T>(value:T) where T: fmt::Debug {
    println!("imment shrinkage {:?}", value);
    
}

fn mutait(bob: Rc<RefCell<Bob>>) {
    bob.borrow_mut().name = "muttttt".to_string();
}

fn main() {
    
    /*
    let b = Bob::new("A");
    println!("xxx");
    //black_home(b);
    //
    //
    */
    
    let mut bob = Bob::new("A");
    for &name in &["B", "C"] {
        println!("before overwrite...");
        bob = Bob::new(name);
        println!("after overwrite ...");
        println!("");
    }


    let bob = Box::new(Bob::new("AA"));

    let bob = Rc::new(Bob::new("BBB"));
    println!("{:?}", bob);

    black_hole(bob.clone());

    let bob = Rc::new(RefCell::new(Bob::new("xxxxx")));
    mutait(bob.clone());
    println!("{:?}", bob);


    let bob = Bob::new("thread");
    let i: i64 = 12;
    let child = thread::spawn(move ||{
        println!("From thread, {:?} and {:?}", bob, i);
    });

    println!("waiting fro thread to end");
    child.join();

}
