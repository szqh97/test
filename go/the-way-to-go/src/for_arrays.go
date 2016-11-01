package main

import (
	"fmt"
)

func main() {
	var arr1 [5]int
	for i := 0; i < len(arr1); i++ {
		arr1[i] = 2 * i
	}
	fmt.Println(arr1)

	a := [...]string{"a", "b", "c", "d"}
	for i := range a {
		fmt.Println("Array item", i, "is", a[i])
	}
}
