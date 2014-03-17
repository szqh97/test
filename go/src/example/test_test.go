package main

import (
	"fmt"
	"math"
	"math/cmplx"
)

var (
	ToBe   bool       = false
	MaxInt uint64     = 1<<64 - 1
	z      complex128 = cmplx.Sqrt(-5 + 12i)
)

func add(x, y int) int {
	return x + y
}

func swap(x, y string) (string, string) {
	return y, x
}

func split(sum int) (x, y int) {
	x = sum * 4 / 9
	y = sum - x
	return
}

func sqrt(x float64) string {
	if x < 0 {
		return sqrt(-x) + "i"
	}
	return fmt.Sprint(math.Sqrt(x))
}
func main() {
	a, b := swap("hello", "world")
	fmt.Println(a, b)
	fmt.Println(split(71))
	const f = "%t(%v)\n"
	fmt.Println(f, ToBe, ToBe)
	fmt.Println(f, MaxInt, MaxInt)
	fmt.Println(f, z, z)
	sum := 0
	for i := 0; i < 10; i++ {
		sum += i
	}
	fmt.Println(sum)
	fmt.Println(sqrt(2), sqrt(-5))

}
