pub fn make_path(parent: &str, child: &str) -> String {
    let mut result = parent.to_owned();
    if parent.chars().last().unwrap() != '/' {
        result.push('/');
    }
    result.push_str(child);
    result
}

#[test]
fn test_make_path() {
    assert_eq!(make_path("/home", "szqh97"), "/home/szqh97");
    assert_eq!(make_path("/home", "szqh97/"), "/home/szqh97/");
    assert_eq!(make_path("/home/", "szqh97"), "/home/szqh97");
    assert_eq!(make_path("/home/", "szqh97/"), "/home/szqh97/");
    
}
