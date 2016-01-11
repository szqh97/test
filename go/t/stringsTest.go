package main
import (
    "fmt"
    "strings"
)

func main(){
    str := "The quick brown fox jumps over the layzy dog"
    sl := strings.Fields(str)
    fmt.Printf("Splitted in slice: %V\n", sl)
    for _, val := range sl {
        fmt.Printf("%s - ", val)
    }
    fmt.Println()
    fmt.Println(strings.LastIndex(str, "o"))

    str2 := "GO1|The ABC of GO|25"
    sl2 := strings.Split(str2, "|")
    fmt.Printf("Splitted in slice: %v\n", sl2)
    for _, val := range sl2{
        fmt.Printf("%s - ", val)
    }
    fmt.Println()

    str3 := strings.Join(sl, ";")
    fmt.Printf("s12 joined by ;: %s\n", str3)
}

