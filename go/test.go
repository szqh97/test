package main
import (
    "fmt"
    "os"
)
func readfile(ch chan []byte){
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
    buf := make ([]byte, 512)
    go readfile(ch)
    buf =<- ch 
    fmt.Println(buf)
    

}

