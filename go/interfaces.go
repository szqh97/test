package main
import "fmt"

type Shaper interface {
    Area() float32
}

type Square struct {
    side float32
}

func (sq *Square) Area() float32 {
    return sq.side * sq.side
}
func main() {
    sql := new (Square)
    sql.side = 4

    areaintf := sql
    fmt.Println("the squre is ", areaintf.Area(), areaintf.side)
}
