package main
import (
    "fmt"
    "math"
)
func gen_pi(ch chan string) {
    var pi float64
    pi = 0
    for i := 0; ; i++ {
        pi += float64(4 / (2*i+1)) *math.Pow(-1, float64(i))
        ch <-fmt.Sprintf("%03.111f", pi)

    }
}
func main() {
    ch := make(chan string)
    go gen_pi(ch)
    for {
        fmt.Println(<-ch)
    }
}
