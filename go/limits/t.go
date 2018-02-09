package main

import "fmt"

func main() {
	ch := make(chan string)
	ch <- "123"
	fmt.Println(<-ch)

}
