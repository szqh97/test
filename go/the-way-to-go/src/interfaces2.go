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
	sq1 := new(Square)
	sq1.side = 5
	areIntf := sq1
	fmt.Println(areIntf.Area())

}
