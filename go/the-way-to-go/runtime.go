package main

import "fmt"
import (
	"runtime"
)

func main() {
	var m runtime.MemStats
	runtime.ReadMemStats(&m)
	fmt.Println("vim-go")
	fmt.Println(m)
	fmt.Print("nextGC:", m.NextGC)
	fmt.Print("LastGC:", m.LastGC)

}
