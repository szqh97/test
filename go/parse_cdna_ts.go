package main
import (
//    "flag"
    //"encoding/binary"
    "fmt"
    "encoding/gob"
    "bytes"
    "os"
    "log"
)

type control_block struct {
    ser_num uint32
    dna_type uint32
    length uint32
    pad uint32
    ts uint64
}

/*
type dna_heaer struct {
    pad [48]byte
}

type dna struct {
    ts uint32
    pad [36]byte
}
*/

func (cb *control_block) GobDecode(buf []byte) error {
    r := bytes.NewBuffer(buf)
    decoder := gob.NewDecoder(r)
    err := decoder.Decode(&cb.ser_num)
    if err != nil {
        return err
    }
    err = decoder.Decode(&cb.dna_type)
    if err != nil {
        return err
    }
    err = decoder.Decode(&cb.length)
    if err != nil {
        return err
    }
    err = decoder.Decode(&cb.pad)
    if err != nil {
        return err
    }
    return decoder.Decode(&cb.ts)
}

func extract_ts(dnafile string) error {
    file, err := os.Open(dnafile)
    if err != nil {
        log.Fatal(err)
    }

    cb_bytes := make ([]byte, 24)
    count, err := file.Read(cb_bytes)
    if err != nil {
        log.Fatal(err)
    }
    fmt.Println(cb_bytes, count)

    buffer := bytes.NewBuffer(cb_bytes)
    dna_cb := new (control_block)
    dec := gob.NewDecoder(buffer)
    err = dec.Decode(dna_cb)
    fmt.Println(dna_cb, err)

    defer file.Close()
    return nil
}

func main() {
    dnafile := "./2.1386403800.cdna"
    //dnafile := flag.NArg(1)
    extract_ts(dnafile)
}
