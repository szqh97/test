package main
import "fmt"
func main() {
    x := Min(1, 2, 3, 4, 5)
    fmt.Printf("The minimum is: %d\n", x)
    arr := []int{2,3,4,5,2,9}
    x = Min (arr...)
    fmt.Printf("The minimum in the array arr is : %d\n", x)
}
func Min(a ...int) int {
    if len(a) == 0{
        return 0
    }
    min := a[0]
    for i, v := range a {
        fmt.Println(i)
        if v < min{
            min = v
        }
    }
    return min
}
