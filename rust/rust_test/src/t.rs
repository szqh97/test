unsafe fn raw_byte_repr<'a, T>(ptr: &'a T) -> &'a [u8]
{
    std::mem::transmute(std::raw::Slice{
        data: ptr as *const _ as *const u8,
        len: std::mem::size_of::<T>(),
    })
}


fn main() {
    #[repr(packed)]
    struct Header {
        some: u8,
        thing: u8,
    }
    let h = Header{some: 1, thing: 0xff};
    unsafe {
        let b = raw_byte_repr(&h);
        //println!("{:?}", raw_byte_repr(&h));
    }
}

