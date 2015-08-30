fn reverse(pair: (i32, bool)) -> (bool, i32) {
    let (interger, boolean) = pair;
    (boolean, interger)
}
fn main() {
    let long_tuple = (1u8, 2u16, 3u32, 4u64, 
                     -1i8, -2i16, -3i32, -4i64,
                     0.1f32, 0.2f64, 'a', true);
    println!("long tuple first values: {}", long_tuple.0);
    println!("long tuple second values: {}", long_tuple.1);

    let t = (-1, false);
    println!("{:?}", reverse(t));

}
