package main
import (
    "strings"
    "fmt"
)
func main(){
    h := "192.168.1.1:8080"
    fmt.Println(strings.Replace(strings.Replace(h, ".", "_", -1), ":", "_", -1))
}
