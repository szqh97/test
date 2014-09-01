package main
import "fmt"

type Shaper interface {
    Area() float32
}

type ToplogicalGenus interface {
    Rank() int
}

type Square struct {
    side float32
}

func (sq *Square) Area() float32{
    return sq.side * sq.side
}

func (sq *Square) Rank() int {
    return 1
}

type Rectangel struct {
    length, width float32
}

func (r Rectangel) Area() float32 {
    return r.width * r.length
}

func (r Rectangel) Rank() int {
    return 2
}

func main () {
    r := Rectangel{5, 3}
    q := &Square{5}
    shapes := []Shaper{r, q}
    fmt.Println("Looping through shapes for area ...")

    for n, _ := range shapes {
        fmt.Println("Shape details: ", shapes[n])
        fmt.Println("Area of shape is: ", shapes[n].Area())
    }

    topgen := []ToplogicalGenus{r, q}
    fmt.Println("Looping through topgen for rank ...")
    for n, _ := range topgen {
        fmt.Println("Shape details: ", topgen[n])
        fmt.Println("Toplogical Genus of this shape is: ", topgen[n].Rank())
    }
}
