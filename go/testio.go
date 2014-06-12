package main
import (
    "io/ioutil"
    "fmt"
)

func main(){
    data,_ := ioutil.ReadFile("./web.go")
    fmt.Println(data)
}
