package main
import (
    "time"
    "fmt"
)
func main() {
    ch1 := make(chan int)
    done := make(chan int)
    go pump(ch1)
    go suck(ch1)
    time.Sleep(1e9)
    <-done

}

func suck(ch chan int) {
    for {
        fmt.Println(<-ch)
    }
}

func pump(ch chan int) {
    for i:=0; ; i++ {
        ch <-i
    }
}
