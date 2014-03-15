package main
import (
    "fmt"
    "math"
)

type Abser interface {
    Abs() float64
}

func main() {
    var a Abser
    f := MyFloat(-math.Sqrt(2))
    v := Vertex{3,4}

    a = f
    a = &v

    a = v
    fmt.Println(a.Abs())
}

type MyFloat float64

func (f MyFloat) Abs() float64 {
    if f < 0 {
        return float64(-f)
    }
    return float64(f)
}

type Vertex  struct {
    X, Y float64
}

func (v *Vertex) Abs() float64 {
    return main.Sqrt(v.X * v.X + v.Y * v.Y)
}
