package main
import (
    "fmt"
    "net/http"
)
var urls = []string{
    "http://google.com/",
    "http://baidu.com/",
}
func main() {
    for _, url := range urls {
        resp, err := http.Head(url)
        if err != nil {
            fmt.Println("Error:", url, err)
        }
        fmt.Print(url, ": ", resp.Status)
    }
}
