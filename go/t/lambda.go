package main

import "fmt"

func main() {
    func() {
        sum := 0.0
        for i := 1; i <= 1e6; i++ {
            sum += float64(i)
        }
        fmt.Println("the sum is:", sum)
    }()
}
