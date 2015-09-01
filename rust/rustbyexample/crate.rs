// Crate name
#![crate_name = "rary"]
// Specify the output type
#![crate_type = "lib"]

pub fn public_func() {
    println!("called rary's 'public_func'");
}

fn private_func() {
    println!("called rary's 'private func");
}

pub fn indirect_func() {
    println!("called rary's 'indirect_func");
    private_func();
}
