//
// This is an eventloop based epoll.

use std::os::unix::io::RawFd;
use errno::errno;
use chrono::*;


trait Handler{
    fn handler_event(fd: RawFd, x:i32) ;
}

struct EventLoop{
    _impl: RawFd,
 //   _peridic_callbacks: Vec<T>,
    model: String,
    _stopping: bool,
    time: DateTime<UTC>,
}

trait Operation {
    fn Add()-> f64;
}

