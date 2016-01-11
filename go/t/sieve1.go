package main
import "fmt"

// send the sequence 2, 3, 4, ... to channel ch
func generate(ch chan int){
    for i := 2; ;i++{
        ch <- i
    }
}

// Copy the values from channel in to channel out
// removing those divisible by prime.
func filter(in, out chan int, prime int){
    for {
        i := <-in
        if i % prime != 0 {
            out <- i
        }
    }
}

func main () {
    ch := make(chan int)
    go generate(ch)
    for {
        prime := <- ch
        fmt.Print(prime, " ")
        ch1 := make(chan int)
        go filter(ch, ch1, prime)
        ch = ch1
    }
}

