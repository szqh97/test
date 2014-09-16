package main
import (
    "os"
    "flag"
)
var NewLine = flag.Bool("n", false, "print on newline")

const (
    Space = " "
    newline = "\n"
)
func main() {
    flag.PrintDefaults()
    flag.Parse()
    var s string = ""
    for i := 0; i < flag.NArg(); i++ {
        if i > 0 {
            s += Space
        }
        s += flag.Arg(i)
    }
    if *NewLine {
        s += NewLine
    }
    os.Stdout.WriteString(s)
}
