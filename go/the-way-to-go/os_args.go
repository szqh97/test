package main
import (
    "os"
    "fmt"
    "strings"
)

func main() {
    who := "Alice "
    if len(os.Args) > 1 {
        who += strings.Join(os.Args[1:], "")
    }
    fmt.Println("Good Morning", who)
}
