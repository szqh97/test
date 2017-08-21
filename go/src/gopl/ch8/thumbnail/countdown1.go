package main

import (
	"fmt"
	"time"
)

func launch() {
	fmt.Println("rocket launch .....")
}
func main() {
	abort := make(chan struct{})
	fmt.Println("Commencing countdown, Press return to abort.")
	select {
	case <-time.After(3 * time.Second):
		fmt.Println("x")

	case <-abort:
		fmt.Println("Launch abort.")
		return

	}
	launch()

}
