package main
import (
    "fmt"
    "net/http"
    "io/ioutil"
    "log"
)
func main(){
    res, err := http.Get("http://www.baidu.com")
    CheckError(err)
    data, err := ioutil.ReadAll(res.Body)
    CheckError(err)
    fmt.Printf("Got: %q", string(data))
}
func CheckError(err error) {
    if err != nil {
        log.Fatal("Get: %v", err)
    }
}
