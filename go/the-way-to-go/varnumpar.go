package main
import (
    "fmt"
)

func main() {
    x := min(1,2,3,4,5,19)
    fmt.Printf("The min is %d\n", x)
    arr := []int{1,2,3,4,5,5,5,0}
    x = min(arr...)
    fmt.Printf("the min in the arr is %d\n", x)
}

func min(a ...int) int{
    if  len(a) == 0 {
        return 0
    }

    min := a[0]
    for _, v := range a {
        if v < min {
            min = v
        }
    }
    return min
}
