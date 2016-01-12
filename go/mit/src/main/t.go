package main
import (
    "container/list"
    "mapreduce"
    "fmt"
)
func main() {
    l := list.New()

    l.PushBack(mapreduce.KeyValue{"a","1"})
    l.PushBack(mapreduce.KeyValue{"b","1"})
    fmt.Printf("%v\n", *l)

    for e := l.Front(); e != nil; e = e.Next() {
        kv := e.Value.(mapreduce.KeyValue)
        fmt.Printf("%v\n", kv)
    }


}
