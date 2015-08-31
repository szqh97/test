fn apply<F>(f: F) where  F: FnOnce(){
    f()
}
fn apply_to_3<F>(f:F) -> i32 where F:Fn(i32)-> i32 {
    f(3)
    
}

fn call_function<F: Fn()>(f:F){
    f()
}

fn call_f<F> (f:F) where F: Fn(){
    f()
}

fn create_fn() -> Box<Fn()> {
    let text = "Fn".to_owned();
    Box::new(move||{
        println!("This is a: {}", text)
    })
}
fn create_fnmut() -> Box<FnMut()> {
    let text = "Fn".to_owned();
    Box::new(move||{
        println!("This is a: {}", text)
    })
}

fn print2() {
    println!("I'm a function")
}

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

    let greeting = "hello";
    
    let mut farewell = "goodbye".to_owned();

    let diary = ||{
        println!("I said {}.", greeting);

        farewell.push_str("!!!");
        println!("Then I screamed {}.", farewell);
        println!("Now I can sleep. zzzzz");
        drop(farewell)

    };

    apply(diary);
    let double = |x| 2*x;
    println!("3 doubled: {}", apply_to_3(double));

    call_f(print2);
    call_function(print2);

    let fn_plain = create_fn();
    let fn_mut = create_fnmut();

    fn_plain();
    fn_mut();
}
