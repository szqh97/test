#[macro_use]
extern crate abomonation;
extern crate rustc_serialize;

use abomonation::*;
//use abomonation::{encode, decode};
use std::io;
use std::io::prelude::*;
use std::fmt;
use std::io::BufReader;
use std::fs::File;
use std::path::Path;
use std::error::Error;

use std::mem;


#[derive(RustcEncodable, RustcDecodable)]
struct dna_header {
    version         : u32,
    media_length    : u32,
    video_format    : u32,
    video_fps       : f32,
    video_width     : i32,
    video_height    : i32,
    video_bitrate   : i32,
    audio_format    : u32,
    audio_sample_format     : i32,
    audio_sample_rate       : i32,
    audio_sample_size       : i32,
    audio_channel           : i32,
}

unsafe_abomonate!(dna_header:
            version,
            media_length,
            video_format,
            video_fps,
            video_width,
            video_height,
            video_bitrate,
            audio_format,
            audio_sample_format,
            audio_sample_rate,
            audio_sample_size,
            audio_channel);
impl dna_header {
    fn new() -> dna_header {
        dna_header {
            version: 1,
            media_length: 0,
            video_format: 0,
            video_fps: 29.9,
            video_width: 0,
            video_height: 0,
            video_bitrate: 0,
            audio_format: 0,
            audio_sample_format: 0,
            audio_sample_rate: 0,
            audio_sample_size: 0,
            audio_channel: 0,
        }
    }

    /*
       fn parse_to_header(head_vec: &[u8; 48]) -> dna_header {

       }
       */
}

impl fmt::Display  for dna_header {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, 
               "dna header info:
        version: {}, 
        media_length: {},
        video_format: {},
        video_fps: {},
        video_width: {},
        video_height: {},
        video_bitrate: {},
        audio_format: {},
        audio_sample_format: {},
        audio_sample_rate: {},
        audio_dample_size: {},
        audio_channle: {}",
        self.version,
        self.media_length, 
        self.video_format,
        self.video_fps,
        self.video_width,
        self.video_height,
        self.video_bitrate,
        self.audio_format,
        self.audio_sample_format,
        self.audio_sample_rate,
        self.audio_sample_size,
        self.audio_channel)
    }
}

#[repr(packed)]
struct dna_frame {
    ts        : u32,
    data    : Vec<u8>,
}

unsafe_abomonate!(dna_frame: ts, data);

impl fmt::Display for dna_frame {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "dna frame info: ts {} ...", self.ts, )
    }
}

impl dna_frame {
    fn new() -> dna_frame {
        dna_frame {
            ts: 0,
            data: vec!(0;36),
        }
    }
}


fn wrap() {
    let file_path = Path::new("/home/szqh97/1.vdna");
    let mut head_buf: [u8; 48] = [0; 48];

    let mut dnafile = match File::open(&file_path) {
        Err(e) => panic!("couln't open file: {}", Error::description(&e)),
        Ok(file) => file,
    };

    //decode dna header
    match dnafile.read(&mut head_buf) {
        Ok(size) => println!("read header length: {}", size),
        Err(e) => panic!("READ error"),
    };

    let dna_head: dna_header = unsafe{mem::transmute(head_buf)};
    println!("{}", dna_head);
    let mut loop_flag = true;
    while loop_flag {
        let mut dna_frame_buf: [u8; 40] = [0;40]; 
        match dnafile.read(&mut dna_frame_buf) {
            Ok(size) => {
                if size == 0 {
                    loop_flag = false;
                }
            }
            Err(e) => panic!("read dna frame error"),
        }

        /*
        let ddd:[u8;6] = [1,2,3,4,5,6];
        let mut ts_buf: [u8;4] = ddd.split_at_mut(4).0;
        assert_eq!(ddd.split_at(4).0, ts_buf);
        */
        //let ts: u32 = unsafe{ mem::transmute::<[u8;4], u32>(ts_buf)};
        //println!("xxxxxts:{}", ts);

       // println!("{}", dna);
    }
}

    fn parse_dna_info () {
        let file_path = Path::new("/home/szqh97/1.vdna");
        let mut buffer = Box::new(Vec::new());
        let mut dnafile = match File::open(&file_path) {
            Ok(file) => file,
            Err(e)=> panic!("couldn't open file: {}", Error::description(&e)),
        };

        match dnafile.read_to_end(&mut buffer) {
            // detect whether file is ok by size..
            Ok(size) => println!("read length: {}, buffer size is {}", size, buffer.len()),
            Err(e) => println!("read error?!"),
        };

        let (mut head_buf, mut dna_data_buf) = buffer.split_at_mut(48);
        
        if let Some((dna_head,remaining)) = unsafe { decode::<dna_header>(&mut head_buf) } {
            println!("ok");
            println!("{}", dna_head);
        }

        let mut exit_flag = false;
        let mut dna_frame_buf:Vec<u8> = Vec::new();
        let mut extra_dna_frames_buf: Vec<u8> = Vec::new();
        let mut tmp_buff: Vec<u8> = Vec::new();
        //let (dna_frame_buf, extra_dna_frames_buf) = dna_data_buf.split_at_mut(40);
        let mut pos: usize = 0;
        while !exit_flag {
            if pos + 40 >= dna_data_buf.len() {
                exit_flag = true;
            }
            let ts: [u8; 4] = [dna_data_buf[pos], dna_data_buf[pos + 1], dna_data_buf[pos+2], dna_data_buf[pos + 3]];
            /*
            if let Some((dna, other)) = unsafe { decode::<dna_frame>(dna_frame_buf) } {
                //println!("{}", dna);
                println!("PPP {}", tmp_buff.len());
            }

            let (dna_frame_buf, extra_dna_frames_buf) = tmp_buff.split_at_mut(40);
            let tmp_buff = extra_dna_frames_buf;
            */

            pos += 40;
            let dna_ts: u32 = unsafe{ mem::transmute::<[u8;4],u32>(ts) };
            println!("dna ts is :{}", dna_ts);

        }


    }

    fn main() {

        parse_dna_info();
        //wrap();

        //let mut reader = BufReader::new(dnafile);

        //    let mut f = mat File::open("~/1.vdna");

    }
