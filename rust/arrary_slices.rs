use std::mem;

fn analyze_slice(slice: &[i32]){
    println!("first element of slice is {}", slice[0]);
    println!("the size of slice is {}", slice.len());
}
fn main() {
    let xs: [i32; 5] = [1,2,3,4,5];
    let ys: [i32; 500] = [0; 500];
    println!("array size {}",ys.len());
    println!("array occupied {}", mem::size_of_val(&xs));
    println!("Borrow the whole array as a slice");
    analyze_slice(&xs);
}
