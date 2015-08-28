pub trait FnOnce<Args> {
    type Output;
    extern "rust-call" fn call_onece(self, args: Args) -> self::Output;
}

pub trait FnMut<Args>: FnOnce<Args> {
    extern "rust-call" fn call_mut(&mut self, args: Args) -> self::Output;
}

pub trait Fn<Args>: FnMut<Args> {
    extern "rust-call" fn call(&self, args: Args) -> self::Output;
}


