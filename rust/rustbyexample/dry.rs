use std::ops::{Add, Mul, Sub};

macro_rules! assert_equal_len {
    ($a:ident, $b:ident, $func:ident, $ops:tt) => (
        assert!($a.len() == $b.len(),
        "{:?}: dimension mismatch:{:?} {:?} {:?}", 
        stringify!($func),
        ($a.len(),),
        stringify!($op),
        ($b.len(),))
    );
}

macro_rules! op {
    ($func:ident, $bound:ident, $op:tt, $method:ident) => (
        fn $func<T:$bound<T, Output=T> + Copy>(xs: &mut Vec<T>, ys: &Vec<T>) {

            
        }
        
    );
}
