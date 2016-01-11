package main
import "fmt"
import "runtime"
import "time"

func main() {
    start := time.Now()
    end := time.Now()
    fmt.Println("costing ...", end.Sub(start))
    var f = Adder()
    _, file, line, _ := runtime.Caller(1)
    fmt.Println(file, line)
    fmt.Print(f(1), " - ")
    fmt.Print(f(20), " - ")
    fmt.Print(f(300), "\n")
}

func Adder() func(int) int{
    var x int
    return func(delta int) int{
        x += delta
        return x
    }
}
