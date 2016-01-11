package main
import (
    "fmt"
)
func sendData(ch chan string) {
    ch <- "aaaa"
    ch <- "bbbb"
    ch <- "dddd"
    close(ch)
}
func getData(ch chan string) {
    for {
        in, open := <-ch
        if !open{
            break;
        }
        fmt.Println(in)
    }
}

func main() {
    ch := make(chan string)
    go sendData(ch)
    getData(ch)

}
