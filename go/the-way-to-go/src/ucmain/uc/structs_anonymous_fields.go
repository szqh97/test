package uc

import "fmt"

type innerS struct {
	in1 int
	in2 int
}

type outerS struct {
	b int
	c float32
	int
	innerS
}

func main() {
	out := new(outerS)
	out.b = 5
	out.c = 6.7
	out.int = 44
	out.in1 = 4
	out.in2 = 3
}
