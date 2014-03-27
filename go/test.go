package main
import (
    "fmt"
    "os"
)
func readfile(ch chan []byte){
    defer close(ch) 
    b := make([]byte, 1024)
    f, err := os.Open("pc.go")
    if err  != nil {
    }
    f.Read(b)
    
    ch <- b
}


var a interface{}
func main() {

    //ch := make(chan []byte, 1024)
    ch := make(chan []byte, 1024)
    go readfile(ch)
    ok := true
    for ok {
        if buf, ok := <-ch; ok {
            fmt.Println(buf)

    }
}


}


