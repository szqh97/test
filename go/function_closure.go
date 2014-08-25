package main
import "fmt"
import "log"
import "runtime"
where := func(){
    _, file, line, _ := runtime.Caller(1)
    log.Printf("%s:%d", file, line)
}
func main() {
    where()
    var f = Adder()
    fmt.Print(f(1), " - ")
    fmt.Print(f(20), " - ")
    fmt.Print(f(300), "\n")
    where()
}

func Adder() func(int) int{
    var x int
    return func(delta int) int{
        x += delta
        return x
    }
}
