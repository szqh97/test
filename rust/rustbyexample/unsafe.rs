fn main() {
    let raw_p: *const u32 = &10;
    unsafe{

    assert!(*raw_p == 10);
    }

    let u:&[u8] = &[40,50,60];
    unsafe{
        assert!(u == std::mem::transmute::<&str,&[u8]>("123"));
    }


}
