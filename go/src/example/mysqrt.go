package main

import (
	"fmt"
)

func Sqrt(x float64) float64 {
	z := float64(1)
	z1 := z - (z*z-x)/(2*x)
	for z != z1 {
		z = z1
		z1 = z - (z*z-x)/(2*x)
	}
	return z
}

func main() {
	fmt.Println(Sqrt(2))
}
