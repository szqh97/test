package main
import (
//    "flag"
    "encoding/binary"
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

type dna_heaer struct {
    pad [48]byte
}

type dna struct {
    ts uint32
    pad [36]byte
}

func extract_ts(dnafile string) error {
    file, err := os.Open(dnafile)
    if err != nil {
        log.Fatal(err)
    }

    var cb control_block
    cb_bytes := make ([]byte, 24)
    count, err := file.Read(cb_bytes)
    err = nil
    if err != nil {
        log.Fatal(err)
    }
    //log.Println(count, dna_cb.length)

    defer file.Close()
    return nil

}

func main() {
    dnafile := "./2.1386403800.cdna"
    //dnafile := flag.NArg(1)
    extract_ts(dnafile)
}
