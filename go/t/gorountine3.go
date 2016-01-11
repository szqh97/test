package main
import "fmt"
func main() {
    ch := make(chan string)
    go sendData(ch)
    getData(ch)
}

func sendData(ch chan string){
    ch <- "a"
    ch <- "b"
    close(ch)
}

func getData(ch chan string) {
    for {
        input, open := <-ch
        if !open{
            break
        }
        fmt.Printf("%s ", input)
    }
}
