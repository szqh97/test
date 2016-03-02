package main
import (
    "container/list"
    "fmt"
    "strings"
)

func Map(value string) *list.List {
    l := list.New()
    word_dict := map[string]int {}
    for _, word := range strings.Split(value, " "){
        if cnt, ok := word_dict[word]; ok {
           cnt += 1
           word_dict[word] = cnt
        } else {
            word_dict[word] = 1
        }
    }
    for k, v := range word_dict {
        l.PushBack(map[string]int {k:v})
    }
    return l
}

func main() {
    l := list.New();
    m := map[string]int {"test": 1}
    l.PushBack(m)


    for pair := l.Front(); pair != nil; pair = pair.Next(){
        if _, ok := pair.Value.(map[string]int)["test"]; ok {
            pair.Value.(map[string]int)["test"] = 111
            fmt.Println("kkkk")
            fmt.Println(l)

        }
    }

    fmt.Println(l)


    li := Map("test kk kk ff kk")
    fmt.Printf("---\n%q\n %d", li, li.Len())
}
