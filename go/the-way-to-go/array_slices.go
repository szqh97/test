package main

import (
	"fmt"
)

func main() {
	var arr1 [6]int
	var slice1 []int = arr1[2:5]
	for i := 0; i < len(arr1); i++ {
		arr1[i] = i
	}

	for i := 0; i < len(slice1); i++ {
		fmt.Printf("Slice at %d is %d\n", i, slice1[i])
	}

	var arr = []int{1, 2, 3, 4}
	fmt.Println("the result is ", sum(arr))

}

func sum(a []int) int {
	s := 0
	for i := 0; i < len(a); i++ {
		s += a[i]
	}
	return s
}
