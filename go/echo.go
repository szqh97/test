package main
import (
    "os"
    "flag"
)
var NewLine = flag.Bool("n", false, "print on newline")

const (
    Space = ""
    Newline = "\n"
)
func main() {
    flag.PrintDefaults()
    flag.Parse()
    var s string = ""
    for i := 0; i < flag.NArg(); i++ {
        if i > 0 {
            s += Space
        }
        if *NewLine {
            s += Newline
        }
        s += flag.Arg(i)
    }
    if *NewLine {
        s += Newline
    }
    os.Stdout.WriteString(s)
}
