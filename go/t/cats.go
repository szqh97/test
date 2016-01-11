package main
import (
    "file"
    "os"
    "fmt"
    "flag"
)

func cat(f *file.File) {
    const NBUF = 512
    var buf [NBUF]byte
    for {
        switch nr, er := f.Read(buf[:]); true {
        case nr < 0:
            fmt.Fprintf(os.Stderr, "cat: error reading from ", f.String(), "to ", er, "\n")
        case nr == 0:
            return 
        case nr > 0:
            if nw, ew := file.Stdout.Write(buf[0:nr]); nw != nr {
                fmt.Println(os.Stderr, "cat error writing from ", f.String(), ew, "\n")
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
