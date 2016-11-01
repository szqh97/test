package main

import (
	"fmt"
	"parse"
)

func main() {
	fmt.Println("vim-go")
	var examples = []string{
		"1 2 3 4 5",
		"2 + 2 = 4",
	}
	for _, ex := range examples {
		nums, err := parse.Parse(ex)
		if err != nil {
			fmt.Println(err)
			continue
		}
		fmt.Println(nums)
	}
}
