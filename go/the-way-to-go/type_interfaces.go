package main

import "fmt"
import "math"

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
	fmt.Println("vim-go")
	var areIntf Shaper
	sq1 := new(Square)
	sq1.side = 5

	areIntf = sq1
	if t, ok := areIntf.(*Square); ok {
		fmt.Printf("The type of areaIntf is: %T\n", t)

	}
	if u, ok := areIntf.(*Circle); ok {
		fmt.Printf("The type of areaIntf is: %T\n", u)
	} else {
		fmt.Println("areIntf dose not containa variable of type Circle")

	}

	classifier(13, 22, 11.22, "kkk", nil, areIntf)
}

func (sq *Square) Area() float32 {
	return sq.side * sq.side
}

func (ci *Circle) Area() float32 {
	return ci.radius * ci.radius * math.Pi
}

func classifier(items ...interface{}) {
	for i, x := range items {
		switch x.(type) {
		case bool:
			fmt.Printf("Param #d is a bool\n", i)
		case int, int64:
			fmt.Printf("Param #d is a int\n", i)
		case string:
			fmt.Printf("Param #d is a string\n", i)
		case float32, float64:
			fmt.Printf("Param #d is a float\n", i)
		case nil:
			fmt.Printf("Param #d is a nil\n", i)
		default:
			fmt.Printf("Param #d is unknown\n", i)
		}
	}
}
