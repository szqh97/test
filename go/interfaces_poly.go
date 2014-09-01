package main
import "fmt"
type Shaper interface {
    Area() float32
}

type Square struct {
    side float32
}

func (sq *Square) Area() float32{
    return sq.side * sq.side
}
func (sq *Square) Color() int {
    return 1
}

type Rectangle struct {
    length, width float32
}

func (r Rectangle) Area() float32 {
    return r.length * r.width
}

func main() {
    r := Rectangle{5, 3}
    q := Square{5}
    c := Square{4}
    shapes := []Shaper{r, &q, &c}

    for n, _ := range shapes {
        fmt.Println("Shape details: ", shapes[n])
        fmt.Println("Aread is : ", shapes[n].Area())
    }
}
