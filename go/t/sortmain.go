package main
import (
    "./sort"
    "fmt"

)
func ints() {
    data := []int{74, 59, 238, -784, 9845, 959, 905, 0, 0, 42, 7586, -5467984, 7586}
    a := sort.IntArray(data)
    sort.Sort(a)
    fmt.Println(a)

}

func main() {
    ints()
}

