package main

import "fmt"

func append(x []int, y int) []int {
	var z []int
	zlen := len(x) + 1
	if zlen < cap(x) {
		z = x[:zlen]
	} else {
		zcap := zlen
		if zcap < 2*len(x) {
			zcap = 2 * len(x)
		}
		z = make([]int, zlen, zcap)
		copy(z, x)
	}

	z[len(x)] = y
	return z
}
func main() {
	var x, y []int
	for i := 0; i < 100; i++ {
		y = append(x, i)
		fmt.Printf("%d cap %d\t%v\n", i, cap(y), y)
		x = y
	}
}
