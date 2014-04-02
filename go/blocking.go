package main

import "fmt"

func f1(in chan int) {
	fmt.Println(<-in)
}
func main() {
	out := make(chan int, 100)
	str := "xx"
	out <- str
	go f1(out)

}
