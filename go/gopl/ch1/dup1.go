package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	counts := make(map[string]int)
	input := bufio.NewScanner(os.Stdin)
	for input.Scan() {
		counts[input.Text()]++
	}

	for l, n := range counts {
		if n > 1 {
			fmt.Printf("%d\t%s\n", n, l)
		}
	}

}
