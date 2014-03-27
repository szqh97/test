package main

import (
    . "autoinc"
    "fmt"
)

func main() {
    ai := New(0, 2)
    defer ai.Close()
    for i := 0; i < 10; i = i + 2 {
            id := ai.Id()
            fmt.Println(id)
    }

}

