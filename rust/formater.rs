use std::fmt::{self, Formatter, Display};

struct City {
    name: &'static str,
    lat: f32,
    lon: f32,
}

impl Display for City {
    fn fmt(&self, f: &mut Formatter) -> fmt::Result {
        let lat_c = if self.lat >= 0.0 {'N'} else {'S'};
        let lon_c = if self.lon >= 0.0 {'E'} else {'W'};

        write!(f, "{}: {:.3}o {} {:.3}o {}", 
              self.name, self.lat.abs(), lat_c, self.lon.abs(), lon_c)
    }
}

fn main() {
    for city in [
        City{name: "Dublin", lat:53.22, lon: -6.777},
        City{name: "Oslo", lat:59.22, lon: 1.9},
        City{name: "Vancouver", lat:49.22, lon:-123.2},
        ].iter(){
            println!("{}", *city);
        }
}
