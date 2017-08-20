package main

import (
	"fmt"
)

func counter(out chan<- int) {

	for x := 0; x < 100; x++ {
		out <- x
	}
	close(out)
}

func squares(out chan<- int, in <-chan int) {
	for v := range in {
		out <- v * v
	}
}

func printer(in <-chan int) {
	for v := range in {
		fmt.Println(v)
	}
}
func main() {
	naturals := make(chan int)
	squares := make(chan int)
	go counter(naturals)
	go squares(squares, naturals)
	printer(squares)
}
