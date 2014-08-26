package main
import "fmt"
func main() {
    map1 := make(map[int]float32)
    map1[1] = 1.0
    map1[2] = 2.0
    map1[3] = 3.0
    map1[4] = 4.0
    map1[5] = 5.0
    for key, val := range map1 {
        fmt.Printf("%d-%f\n", key, val)
    }
}
