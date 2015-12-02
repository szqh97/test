use std::cell::Cell;
use std::cell::RefCell;
fn refcell_test() {
    let x = RefCell::new(vec![1,2,3,4]);
    {
        println!("{:?}", *x.borrow());
    }

    {
        let mut my_ref = x.borrow_mut();
        my_ref.push(1);
        println!("{:?}", my_ref);
    }

}

fn cell_test() {
     {
        let x = Box::new(1);
        let y = x;
        println!("y is {}", y);
    }


    {
        let x = Cell::new(1);
        let y = &x;
        let z = &x;
        x.set(2);
        y.set(3);
        z.set(4);
        println!("{}", x.get());
    }

/*
    {
        let mut x = 1;
        let y = &mut x;
        let z = &mut x;
        x = 2;
        *y = 3;
        *z = 4;
        println!("{}", x);


    }
    */
   
}
fn main() {
    refcell_test();
}

