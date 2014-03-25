package main
import (
    "flag"
    "encoding/binary"
    "fmt"
    "os"
    "log"
)

type control_block struct {
    Ser_num uint32
    Dna_type uint32
    Length uint32
    Pad uint32
    Ts uint64
}

type dna_heaer struct {
    Version uint32
    Media_length uint32
    Pad [40]byte

}

type dna struct {
    Ts uint32
    Pad [36]byte
}

func extract_ts(dnafile string) error {
    file, err := os.Open(dnafile)
    if err != nil {
        log.Fatal(err)
    }
    defer file.Close()
    var (
        cb control_block
        //dnaframe dna
    )

    pos, err := file.Seek(72, os.SEEK_SET)

    if err != nil {
        log.Fatal("set pos: ", pos, err)
    }

    /*
    err = binary.Read(file, binary.LittleEndian, &cb)
    if err != nil {
        log.Fatal("read cb error: ", err)
        return err
    }
    err = binary.Read(file, binary.LittleEndian, &dh)
    if err != nil {
        log.Fatal("read dna header error: ", err)
        return err
    }
    */
    //ts_slice := make([]uint32,100,512)
    err = binary.Read(file, binary.LittleEndian, &cb)
    if err != nil {
        log.Fatal("read cb error: ", err)
        return err
    }
    for ;cb.Length != 0; {
        dna_cnts := cb.Length / 40
        dnas := make ([]dna, dna_cnts)
        err = binary.Read(file, binary.LittleEndian, &dnas)
        for i := 0; i < int(dna_cnts); i++ {
            fmt.Println( dnas[i].Ts)
        }
        err = binary.Read(file, binary.LittleEndian, &cb)
        if err != nil {
            log.Fatal("read cb error 2: ", err)
            return err
        }

    }

    //fmt.Println(ts_slice)
    return nil
}

func main() {
    flag.Parse()
    if flag.NArg() == 0 {
        log.Println("Usage : ./parse_cdna_ts 16.xx.cdna")
    }else {

        dnafile := flag.Arg(0)
        //dnafile := "./16.1394089199.cdna"
        //dnafile := flag.NArg(1)
        extract_ts(dnafile)
    }
}
