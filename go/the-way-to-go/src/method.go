package main

import "fmt"

type vector []int

func (v vector) Sum() (s int) {
	for _, x := range v {
		s += x
	}
	return
}

func main() {
	fmt.Println(vector{1, 2, 3, 4}.Sum())
}
