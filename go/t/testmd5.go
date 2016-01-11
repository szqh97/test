package main
import (
    "crypto/md5"
    "fmt"
    "io"
    "os"
)
func main(){
    name, err := os.Hostname()
    if err != nil {
        fmt.Println("xxxxx")
    }
    h := md5.New()
    io.WriteString(h, name)
    fmt.Println(name, h)

}

