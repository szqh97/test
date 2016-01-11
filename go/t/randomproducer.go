package main
import (
    "fmt"
)
func radomproducer(c chan int64, max int) {
    defer close(c)
    for i := 0; i < max; i++ {
        select {
        case c <- 0:
        case c <- 1:
        }
    }
}

func main() {
    ch := make(chan int64)
    go radomproducer(ch, 100)
    for i:=0; i < 100; i++{
        fmt.Println(<-ch)
    }
}
