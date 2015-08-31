use std::thread;
use std::sync::{Mutex, Arc};

struct Philosopher {
    name: String,
    left: usize,
    right: usize,
}
struct Table {
    forks: Vec<Mutex<()>>,
}

impl Philosopher {

    fn new(name: &str, left: usize, right: usize) -> Philosopher {
        Philosopher{name: name.to_string(),
            left: left,
            right: right,
        }
    }

    fn eat(&self, table: &Table) {
        let _left = table.forks[self.left].lock().unwrap();
        let _right = table.forks[self.right].lock().unwrap();
        println!("{} is eating... ", self.name);
        thread::sleep_ms(1000);
        println!("{} is done eating .", self.name);
    }
    
}

fn main() {
    let table = Arc::new(Table{forks: vec![
        Mutex::new(()),
        Mutex::new(()),
        Mutex::new(()),
        Mutex::new(()),
        Mutex::new(()),
        ]});
    let philosophers = vec![
     Philosopher::new("Judith Butler", 0, 1),
     Philosopher::new("Gilles Deleuze",1,2),
     Philosopher::new("Karl Mar",2,3),
     Philosopher::new("Emma Goldman",3,4),
     Philosopher::new("Michel Foucalt",4,0),
    ];
    
    let handlers: Vec<_> = philosophers.into_iter().map(|p|{
        let table = table.clone();
        thread::spawn(move|| {
           p.eat(&table) ;
        })
    }).collect();

    for h in handlers{
        h.join().unwrap();
    }
}

