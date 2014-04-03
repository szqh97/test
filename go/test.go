package main

import (
	"fmt"
	"os"
)

func main() {
	var m map[int]int
	fmt.Println(len(m))
	fmt.Println(m[4])
	if v, ok := m[4]; ok {
		fmt.Println("map has this key", v)
	} else {
		fmt.Println("map not has this key")
	}
	fmt.Println("x", os.Getpid())
	var a interface{}
	fmt.Println(fmt.Sprintf("xx", a))
    fmt.Println(float64(7/9.0))

}
