package main
import (
    "fmt"
    "io/ioutil"
    "github.com/bitly/go-simplejson"
)
func main(){
    data, _ := ioutil.ReadFile("t.json")
    js, _:= simplejson.NewJson(data)
    d, _ := js.Get("duration").Int()
    taskDNAs, _ := js.Get("taskDNA").Array()

    for  tid := range taskDNAs{
        //url, _ := js.Get("taskDNA").GetIndex(tid).Get("downloadUrl").String()
        url, _ := js.Get("taskDNA").GetIndex(tid).Get("downloadUrl").String()
        fmt.Println(url)
    }
    fmt.Println(d)

}
