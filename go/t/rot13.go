package main

import (
    "file"
    "fmt"
    "os"
    "flag"
)

var rot13Flag = flag.Bool("rot13", false, "rot13 the input")

type reader interface {
    Read(b []byte) (ret int, err error)
    String () string
}

type rotate13 struct {
    source reader
}

func newRotate13(source reader) *rotate13 {
    return &rotate13{source}
}

func (r13 *rotate13) Read(b []byte) (ret int, err error) {
    r, e := r13.source.Read(b)
    /*
    for i :=0; i < r; i++ {
        b[i] = b[i]
    }
    */
    return r, e
}

func (r13 *rotate13) String() string {
    return r13.source.String()
}


func cat(r reader) {
    const NBUF = 512
    var buf [NBUF]byte

    if *rot13Flag {
        r = newRotate13(r)
    }
    for {
        switch nr, er := r.Read(buf[:]); {
        case nr < 0:
            fmt.Println(os.Stderr, "cat: error reading from ", r.String(), er)
            os.Exit(1)
            case nr == 0:  // EOF
            return
        case nr > 0:
            nw, ew := file.Stdout.Write(buf[0:nr])
            if nw != nr {
                fmt.Println(os.Stderr, "cat: error writing from %s: %s\n", r.String(), ew)
            }
        }
    }
}

func main(){
    flag.Parse()
    if flag.NArg() == 0 {
        cat (file.Stdin)
    }
    for i := 0; i < flag.NArg(); i++ {
        f, err := file.Open(flag.Arg(i), 0,0)
        if f == nil {
            fmt.Fprintf(os.Stderr, "cat: can't open %s: error %s\n", flag.Arg(i), err)
            os.Exit(1)
        }
        cat (f)
        defer f.Close()
    }
}
