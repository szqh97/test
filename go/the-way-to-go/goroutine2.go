package main
import (
    "fmt"
    "time"
)

func main() {
    ch := make(chan string)
    go SendData(ch)
    go getData(ch)
    time.Sleep(1e9)
}
func getData(ch chan string) {
    var input string
    for {
        input = <-ch
        fmt.Printf("%s ", input)
    }
}

func SendData(ch chan string){
    ch <- "Washington"
    ch <- "Tripoli"
    ch <- "London"
    ch <- "Beijing"
    ch <- "Tokio"
}
