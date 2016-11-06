package main

import (
	"fmt"
)

func f1(in chan int) {
	fmt.Println(<-in)
}
func f2(out chan int) {
	out <- 2
}

func main() {
	out := make(chan int)
	//out <- 2
	go f2(out)

	go f1(out)
}
