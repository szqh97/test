package main
import (
	"fmt"
)
func main() {
	var value int
	var isPresent bool

	map1: = make(map[string]int)
	map1["New Delhi"] = 55
	map1["Beijing"] = 20
	map1["Washingto"] = 25

	value, isPresent = map1["Beijing"]
	
}
