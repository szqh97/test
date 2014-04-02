package main

import (
	"fmt"
	"time"
)

func longWait() {
	fmt.Println("Beginning longWait()")
	time.Sleep(5 * 1e9)
	fmt.Println("At the end of longWait()")
}

func shortWait() {
	fmt.Println("Beginning shortWait()")
	time.Sleep(2 * 1e9)
	fmt.Println("At the end shortWait()")
}
func main() {
	fmt.Println("In main()")
	go longWait()
	go shortWait()
	fmt.Println("About to sleep in main()")
	time.Sleep(10 * 1e9)
	fmt.Println("At the end of main()")
}
