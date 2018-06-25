package main

import (
	"fmt"
	"time"
)

func f() int {
	bpanic := false

	defer func() {
		fmt.Println("2")
		if err := recover(); err != nil {
			fmt.Println(err)
		}
		fmt.Println("3")
		bpanic = true

	}()
	for {
		fmt.Println("1")
		a := []string{"a", "B"}

		fmt.Println(a[3])
		fmt.Println(4)
		time.Sleep(time.Second * time.Duration(1))

	}
	if bpanic {
		fmt.Println(bpanic)

		return 1
	}

	return 0
}

func main() {
	i := 13
	i = f()
	fmt.Println("xxx")
	fmt.Println("kkk", i)

}
