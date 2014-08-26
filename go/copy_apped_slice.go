package main
import "fmt"
func main() {
    sl_from := [] int {1, 2}
    sl_to := make([]int, 10)
    n := copy(sl_to, sl_from)
    fmt.Println(sl_to)
    fmt.Printf("Copied %d elements\n", n)

    sl3 := []int{1, 2, 3}
    sl3 = append(sl3, 4, 5, 6)
    fmt.Println(sl3)
    fmt.Println("xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx")
    a := []int {1, 2, 3, 4, 5, 6, 7, 8, 9}
    fmt.Println(append(a[:4], a[6:]...))
    fmt.Println(append(a[:5], append([]int{100}, a[5:]...)...))
}
