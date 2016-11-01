package main

import (
	"fmt"
)

func badCall() {
	panic("bad end")
}

func test() {
	defer func() {
		if err := recover(); err != nil {
			fmt.Printf("Panicing %s\r\n", err)
		}
	}()
	badCall()
	fmt.Printf("After bad call\r\n")
}

func main() {
	fmt.Printf("calling test\r\n")
	test()
	fmt.Printf("testing completed\r\n")
}
