package main
import "fmt"

var a interface{}
func f() interface{} {
    return 444
}
func main() {
    var i int = 5
    s := "Hello World"
    a = i
    fmt.Println(a)
    a = s
    fmt.Println(a)
    fmt.Println(f())
}

