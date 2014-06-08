package main
import (
    "fmt"
    "time"
)

var week time.Duration

func main() {
    t := time.Now()
    fmt.Println(t)

    fmt.Println(time.Now().UTC())


}
