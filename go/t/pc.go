package main

import (
	"encoding/binary"
	"errors"
	"flag"
	"fmt"
	"os"
)

type control_block struct {
	Ser_num  uint32
	Dna_type uint32
	Length   uint32
	Pad      uint32
	Ts       uint64
}

/*
type dna_heaer struct {
    pad [48]byte
}
*/

type dna struct {
	Ts  uint32
	Pad [36]byte
}

func (cb *control_block) Parse_cb(cb_buf []byte) error {
	if len(cb_buf) != 24 {
		return errors.New("length of cb_buf error")
		fmt.Println('a')
	}
	cb.Ser_num = binary.LittleEndian.Uint32(cb_buf[0:4])
	cb.Dna_type = binary.LittleEndian.Uint32(cb_buf[4:8])
	cb.Length = binary.LittleEndian.Uint32(cb_buf[8:12])
	cb.Pad = binary.LittleEndian.Uint32(cb_buf[12:16])
	cb.Ts = binary.LittleEndian.Uint64(cb_buf[16:24])
	return nil
}

func (d *dna) Parse_dna(dna_buf []byte) error {
	if len(dna_buf) != 40 {
		return errors.New("length of dna_frame error")
	}
	d.Ts = binary.LittleEndian.Uint32(dna_buf[0:4])
	return nil
}

func extract_ts(filename string) error {
	file, err := os.Open(filename)
	defer file.Close()
	if err != nil {
		return errors.New("open file error")
	}
	file.Seek(24+48, os.SEEK_SET)
	cb_buf := make([]byte, 24)
	cb := new(control_block)
	dna_frame := new(dna)
	file.Read(cb_buf)
	cb.Parse_cb(cb_buf)
	dna_buf := make([]byte, cb.Length)
	for cb.Length != 0 {
		file.Read(dna_buf)
		for i := 0; i < int(cb.Length/40); i++ {
			dna_frame.Parse_dna(dna_buf[i*40 : (i+1)*40])
			fmt.Println(dna_frame.Ts)
		}
		file.Read(cb_buf)
		cb.Parse_cb(cb_buf)
	}

	return nil

}

func main() {
	flag.Parse()
	dnafile := flag.Arg(0)
	extract_ts(dnafile)
}
