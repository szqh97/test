#[allow(dead_code)]
#[derive(Debug)]
enum Color {
    Red,
    Blue,
    Green,
    RGB(u32, u32, u32),
    HSV(u32, u32, u32),
    HSL(u32, u32, u32),
    CMY(u32, u32, u32),
    CMYK(u32, u32, u32, u32),
}

fn main() {
    let color = Color::RGB(122, 123,121);
    println!("What color is it?");
    match color {
        Color::Red => println!("The color is Red"),
        Color::Blue => println!("The color is Blue"),
        Color::Green => println!("The color is Green"),
        Color::RGB(r, g, b) => println!("Red:{}, Green:{}, Blue:{}", r, g, b),
        Color::HSV(h, s, v) => println!("Hue:{}, saturation:{}, value:{}", h, s, v),
        Color::HSL(h, s, l) => println!("Hue:{}, saturation:{}, lightness:{}", h, s, l),
        Color::CMY(c, m, y) => println!("Cyan:{}, magents:{}, yellow:{}", c, m, y),
        Color::CMYK(c, m, y, k) => println!("Cyan:{}, magents:{}, yellow:{}, key:{}", c, m, y, k),

    }

    let reference = &4;
    match reference {
        val  => println!("Got a value via destructing: {:?}", val),
    }
    match *reference {
        val  => println!("Go a value via dereferencing: {:?}", val),
    }
}
