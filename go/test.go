package main
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
    

}


