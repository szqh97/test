package main
<<<<<<< HEAD
import "fmt"
import "os"

var a interface{}
func f() interface{} {
    return 444
}
func read (ch chan []byte) {
    buf := make ([]byte, 128)
    buf <-ch
    fmt.Println(buf)
}
func main() {
    var i int = 5
    s := "Hello World"
    a = i
    fmt.Println(a)
    a = s
    fmt.Println(a)
    fmt.Println(f())
    rn :=rune(i)
    fmt.Println(uint32(rn))
    ch := make(chan []byte, 1024)
    file, err := os.Open("./pc.go")
    if err != nil {
    }
    buf := make([]byte, 128)
    file.Read(buf)
    ch<-buf
=======
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
>>>>>>> eba67460dbf0cb736230f0ce66717f4460ab5e43
    

}


