package main
import (
    "fmt"
)
func doSomething(i int, xi float64) float64 {
    fmt.Println(i, xi)
    return float64(i)+xi
}

func main(){
    type Empty interface{}
    var empty Empty
    N := 5

    data := make ([]float64, N)
    res := make ([]float64, N)
    sem := make(chan Empty, N)
    copy(data, []float64{0.1, 0.2, 0.3, 0.4, 0.5})

    for i, xi := range data {
        go func(i int, xi float64) {
            res[i] = doSomething(i, xi)
            fmt.Println("i", len(sem))
            sem <- empty
        }(i, xi)

    }

    for i:= 0; i < N; i++ {
        <-sem
        fmt.Println("x", len(sem))
    }
}
