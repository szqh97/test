mod checked {
    #[derive(Debug)]
    pub enum MathError {
        DivisionByZero,
        NegativeLogarithm,
        NegativeSquareRoot,
    }

    pub type MathResult = Result<f64, MathError>;
    pub fn div(x:f64, y:f64) -> MathResult {
        if y == 0.0 {
            Err(MathError::DivisionByZero)
        } else {
            Ok(x / y)
        }
    }

    pub fn sqrt(x: f64) -> MathResult {
        if x < 0.0 {
            Err(MathError::NegativeSquareRoot)
        } else {
            Ok(x.ln())
        }
    }
}

    fn op(x: f64, y: f64) -> f64 {
        match  checked::div(x,y) {
            Err(Why) => panic!("{:?}", Why),
            Ok(ln) => match checked::sqrt(ln) {
                Err(Why) => panic!("{:?}", Why),
                Ok(sqrt) => sqrt,
            },
        }
    }

fn main() {
    println!("{}", op(1.0, 1.0));
}
