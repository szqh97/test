package main
import (
    "fmt"
    "time"
    "runtime"
)

func pump1 (ch chan int) {
    for i:= 0; ; i++ {
        ch <- i*2
    }
}

func pump2 (ch chan int) {
    for i := 0; ; i++ {
        ch <- i+5
    }
}

func suck (ch1, ch2 chan int) {
    for {
        select {
        case v:= <-ch1:
            fmt.Println("Received on channel1: ", v)
        case  v:= <-ch2:
            fmt.Println("Received on channe2: ", v)
        }
    }
}
func main(){
    runtime.GOMAXPROCS(2)
    ch1 := make (chan int)
    ch2 := make (chan int)

    go pump1(ch1)
    go pump2(ch2)
    go suck(ch1, ch2)
    time.Sleep(1e9)
}
