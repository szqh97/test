package main
import (
    "fmt"
)

func main() {
    // A
    items := make([]map[int]int, 5)
    for i := range items {
        items[i] = make (map[int]int, 1)
        items[i][1] =2
    }
    fmt.Printf("Version A: %v\n", items)

    items2 := make([]map[int]int, 5)
    for _, item := range items2 {
        item = make(map[int]int, 1)
        item[1] = 2
    }
    fmt.Printf("Version B: %v\n", items2)
}
