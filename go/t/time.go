package main
import (
    "fmt"
    "time"
)

var week time.Duration

func main() {
    t := time.Now()
    fmt.Println(t)
    fmt.Println(t.Location())
    fmt.Println(t.Zone())

    fmt.Println(time.Now().UTC())
    fmt.Println(t.Format("02 Jan 2006 15:04"))


}
