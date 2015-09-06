extern crate rustc_serialize;
extern crate docopt;

use docopt::Docopt;

static USAGE: &'static str =r#"Usage: wc [options] [<file>]

Options:
    -c, --bytes  print the byte counts
    -m, --chars  print the character counts
    -l, --lines  print the newline counts
    -w, --words  print the word counts
    -L, --max-line-length  print the length of the longest line
    -h, --help  display this help and exit
    -v, --version  output version information and exit"#;

#[derive(RustcDecodable)]
#[derive(Debug)]
struct Args {
    arg_file: Option<String>,
    flag_bytes: bool,
    flag_chars: bool,
    flag_lines: bool,
    flag_max_line_length: bool,
}

fn main() {
    let args:Args = Docopt::new(USAGE).and_then(|d| d.decode()).unwrap_or_else(|e| e.exit());
    let docopt = match Docopt::new(USAGE) {
        Ok(d) => d,
        Err(e) => e.exit(),
    };
    //println!("{:?}", docopt);

    let args:Args = match docopt.decode() {
         Ok(args) => args,
         Err(e) => e.exit(),
    };

    //println!("Counting stuff in {}", args.arg_file.unwrap_or("standard input").to_string());
    if args.flag_bytes {
        println!("Counting bytes");
    }
    if args.flag_chars {
        println!("Counting characters!");
    }


}
