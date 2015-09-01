fn function() {
    println!("called 'function'");
}

mod my {
    #[allow(dead_code)]
    pub fn function() {
        println!("called 'my::function'");
    }
    pub mod nested {
        #[allow(dead_code)]
        pub fn function(){
            println!("called 'my::nested::function'");
        }
    }
}

fn main() {
    function();
    my::function();
    my::nested::function();
}
