package main
import "fmt"
type testInt func(int) bool

func isOdd(interger int) bool {
    if interger %2 == 0 {
        return false
    }
    return true
}

func isEven(interger int) bool {
    return !isOdd(interger)
}

func filter(slice []int, f testInt) []int {
    var result []int
    for _, value := range slice {
        if f(value) {
            result = append(result, value)
        }
    }
    return result
}

func main() {
    slice := []int{ 1,2,3,4,5,6,7,8}
    fmt.Println("Slice = ", slice)
    odd := filter(slice, isOdd)
    fmt.Println("Odd elements of slice are:", odd)
    even := filter(slice, isEven)
    fmt.Println("Odd elements of slice are:", even)
}
