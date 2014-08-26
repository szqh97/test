package main
import "fmt"
func main() {
    slice1 := make ([]int, 0, 10)
    for i := 0; i < cap(slice1); i++{
        slice1 = slice1[0:i+1]
        slice1 [i] = i
        fmt.Printf("The lenght of slice is %d, cap is %d\n", len(slice1), cap(slice1))
    }
    s := slice1[5:5]
    fmt.Printf("The lenght of slice is %d, cap is %d\n", len(s), cap(s))

}
