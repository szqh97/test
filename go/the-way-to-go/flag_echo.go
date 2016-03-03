package main
import (
    "os"
    "flag"
)

var NewLine = flag.Bool("n", false, "print newline")

const (
    Space = " "
    Newline = "\n"
)

func main() {
    flag.PrintDefaults()
    flag.Parse()
    var s string = ""
    for i := 0; i < flag.NArg(); i++ {
        if i > 0{
            s += " "
            if *NewLine {
                s += Newline
            }
        }
        s += flag.Arg(i)
    }
    os.Stdout.WriteString(s)
}
