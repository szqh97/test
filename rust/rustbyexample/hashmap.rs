use std::collections::HashMap;

fn call(number: &str) -> &str {
    match number {
        "798-1346" => "we are sorry, the call cannot be completed as dairied. Pleased hang up and try again.",
        "645-7689" => "Hello, This is Mr. Awesome's Pizza. my name is Fred. What can I do for you?",
        _ => "Hi Who is thart again?",

    }
}

fn main() {
    let mut contacts = HashMap::new();

    contacts.insert("Dannel", "798-1346");
    contacts.insert("Ashley", "645-7689");
    contacts.insert("Katile", "435-8291");
    contacts.insert("Robert", "956-1170");
    match contacts.get(&"Dannel") {
        Some(&number) => println!("Calling Dannel: {}", call(number)),
        _ => println!("Don't have Dannel's number"),
    }

}
