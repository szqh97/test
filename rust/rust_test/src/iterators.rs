fn main() {
    for x in 0..10{
        let i = x;
    }

    let mut range = 0..10;
    loop {
        match range.next() {
            Some(x) => {
                let i = x;
            }
            None => {break}
        }
    }

    let nums = vec![1,2,3];
    for num in &nums {
        //println!("num is {:?}", num);
        let n = num;
    }

    let one_to_hundred = (1..1).collect::<Vec<_>>();
    for x in &one_to_hundred {
        println!("item: {}", *x);
    }

    let greater_than_40 = (0..100).find(|x| *x > 40);
    println!("{}", greater_than_40.unwrap());
    match greater_than_40 {
        Some(x) => println!("Found a match {}!", x),
        None => println!("not found a match"),
    }

    let sum = (1..1).fold(0, |sum, x| sum + x);
    println!("sum is {}", sum);

    for i in  (1..1).map(|x| {x +1; x+3}){
        println!("{:?}", i);
    }

    for i in (1..).take(1){
        println!("{}", i);
    }

    let a = [1,2,3,4,5];
    assert_eq!(a.iter().last(), Some(&5));
    assert_eq!(a.iter().count(), 5);
    let mut it = a.iter();
    assert_eq!(it.nth(2), Some(&3));
    assert_eq!(it.nth(2), None);

    let a = [1,2];
    let b = [3,4];
    let mut it = a.iter().chain(&b);
    assert_eq!(it.next(), Some(&1));
    assert_eq!(it.next(), Some(&2));
    it.next();
    it.next();
    assert_eq!(it.next().is_none(), true);

    let a = [0];
    let b = [1];
    let mut it = a.iter().zip(&b);
    assert_eq!(it.next(), Some((&0,&1)));
    assert_eq!(it.next().is_none(), true);

    let xs = [100, 200, 300];
    let mut it = xs.iter().cloned().peekable();
    assert_eq!(*it.peek().unwrap(), 100);


    let a = [1,2,3,4];
    let mut it = a.iter().skip_while(|&a| *a<3);
    assert_eq!(it.next(), Some(&3));
    assert_eq!(it.next(), Some(&4));
    assert_eq!(it.next().is_none(), true);




}
