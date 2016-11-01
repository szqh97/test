package main
import (
    "fmt"
    "strings"
    "time"
)

func main() {
    //seps := " ,./?;:''[]{}!@#$%^&*()-=_+""`"
    str := "Split slices s into all substrings separated by sep and returns a slice of the substrings between those separators. "
    list := strings.Split(str, " ")

    for _, v := range list {
        fmt.Println( v)
    }
    fmt.Printf("%q\n", list)
    fmt.Println(time.Now())
}
