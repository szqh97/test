//#[link(name="shell", version="0.01")]
#![crate_type="lib"]

extern crate log;

pub fn test_log() {
    info!("test log info.");
    debug!("test log info.");
    error!("test log info.");
    
}

