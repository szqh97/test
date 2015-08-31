fn main() {
    fn function (i:i32) -> i32 {i + 1}
    let closure_annotated = |i: i32| -> i32 {i + 1};
    let closure_inferred = |i | i + 1;

    let i = 1;
    println!("function : {}", function(i));
    println!("closure_annotated closured: {}",  closure_annotated(i));
    println!("inferred closure: {}", closure_inferred(i));


    let one = || 1;
    println!("closure returnning one: {}",  one());
    let professor_x = "Charles xavire";
    let print = || println!("Professor X's name is :{}", professor_x);
    print();
}
