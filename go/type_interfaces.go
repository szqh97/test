package main
import (
    "fmt"
    "math"
)

type Square struct {
    side float32
}

type Circle struct {
    radius float32
}

type Shaper interface {
    Area() float32
}

func main() {
    var areaIntf Shaper
    sql := new(Square)
    sql.side = 5

    areaIntf = sql

    if t, ok := areaIntf.(*Square); ok {
        fmt.Printf("The type of areaIntf is: %T\n ", t)
    }
    if u, ok := areaIntf.(*Circle); ok {
        fmt.Printf("The type of areaIntf is: %T\n", u)
    }else {
        fmt.Print("areaIntf does not contain a variable of tyep Circle\n")
    }
}

func (sq *Square) Area() float32 {
    return sq.side * sq.side
}
func (ci *Circle) Area() float32 {
    return ci.radius * ci.radius * math.Pi
}


