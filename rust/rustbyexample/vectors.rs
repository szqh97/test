fn main() {
    let collector_iters: Vec<i32> = (90..100).collect();
    println!("collect 90..100 is {:?}", collector_iters);

    let mut xs = vec![1i32, 4, 5];
    println!("xs is {:?}", xs);

    xs.push(10);
    println!("xs is {:?}", xs);


    println!("the length of xs is {}", xs.len());
    println!("get last item {:?}", xs.pop());
    println!("get last item {:?}", xs[:]);
}
