macro_rules! foo {
    ($v:ident) => (
        let $v = 33
    );
}

macro_rules! Foo {
    () => (
        fn x () {}
    );
}
macro_rules! write_html {
    ($w:expr,) => (());
    ($w:expr, $e:tt) => (write!($w, "{}",$e));
    ($w:expr, $tag:ident [ $($inner:tt)* ] $($rest:tt)*) => {{
        write!($w, "<{}>", stringify!($tag));
        write_html!($w, $($inner)*);
        write!($w, "</{}>", stringify!($tag));
        write_html!($w, $($rest)*);
    }}
}
fn main() {
    use std::fmt::Write;
    let mut out = String::new();
    write_html!(&mut out, 
                htlm[
                head[title["Macros guidooe"]]
                body[h1["macros is the best"]]
                ]);
    println!("{}", out);
    foo!(x);
    println!("{}", x);

}
