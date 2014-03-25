package main
import (
//    "flag"
    "errors"
    "encoding/binary"
    "fmt"
//    "reflect"
   // "io/ioutil"
 //   "encoding/gob"
   "bytes"
    "os"
    //"log"
)

type control_block struct {
    Ser_num uint32
    Dna_type uint32
    Length uint32
    Pad uint32
    Ts uint64
}
/*
type dna_heaer struct {
    pad [48]byte
}
*/

type dna struct {
    Ts uint32
    Pad [36]byte
}

func (cb *control_block) read_cb(cb_buf []byte) error {
    if len(cb_buf) != 24 {
        return errors.New("length of cb_buf error")
    }
    cb.Ser_num = binary.LittleEndian.Uint32(cb_buf[0:4])
    cb.Dna_type = binary.LittleEndian.Uint32(cb_buf[4:8])
    cb.Length = binary.LittleEndian.Uint32(cb_buf[8:12])
    cb.pad = binary.LittleEndian.Uint32(cb_buf[12:16])
    cb.Ts = binary.LittleEndian.Uint32(cb_buf[16:24])
    return nil
}

func (d *dna) read_dna(dna_buf []byte) error {
    if len(dna_buf) != 40 {
        return errors.New("length of dna_frame error")
    }
    d.Ts = binary.LittleEndian.Uint32(dna_buf[0:4])
    copy(d.Pad, dna_buf[4:40])
    return nil
}

func extract_ts(file string) error {
    file := os.Open(file)
    file.Seek(24+48, os.SEEK_SET)

}

func main() {
    //l := intDataSize(dnas)

    dnafile := "./16.1394089199.cdna"
    file, err := os.Open(dnafile)
    if err != nil {
        fmt.Println("xx", err)

    }
    cb_buf := make([]byte, 240)
    //file.Seek(24+48, os.SEEK_SET)
    file.Read(cb_buf)
    r := bytes.NewReader(cb_buf)
    cb, err := read_cb(r)
   //dnafile := flag.NArg(1)
    //extract_ts(dnafile)
}
