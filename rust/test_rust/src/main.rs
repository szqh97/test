use std::collections::HashMap;
use std::cell::RefCell;
use std::rc::Rc;
fn main() {

    println!("Hello, world!");
    let shared_map: Rc<RefCell<_>> = Rc::new(RefCell::new(HashMap::new()));

    shared_map.borrow_mut().insert("africa", 92388);


}
