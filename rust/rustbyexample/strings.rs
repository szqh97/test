fn main() {
    let pangram: &'static str = "the quick brown fox jumps over the lazy dog";
    println!("pang: {}", pangram);

    for word in pangram.split_whitespace().rev() {
        println!("> {}", word);
    }

    let mut chars: Vec<char> = pangram.chars().collect();
    chars.sort();
    chars.dedup();

    let mut string = String::new();
    for c in chars{
        string.push(c);
        string.push_str(", ");
    }

    let chars_to_trim: &[char] = &[' ', ' '];
    let trimmed_str: &str = string.trim_matches(chars_to_trim);
    println!("used characters: {}", trimmed_str);


    let alice = String::from("I like dogs");
    let bob: String = alice.replace("dog", "cat");

    println!("Alice says: {}", alice);
    println!("Bob Says: {}", bob);;
}
