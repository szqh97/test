package uc

import "fmt"

type TwoInts struct {
	a, b int
}

func main() {
	two1 := new(TwoInts)
	two1.a = 12
	two1.b = 10

	fmt.Println(two1.AddThen())
	fmt.Print(two1.AddToParam(111))

}

func (tn *TwoInts) AddThen() int {
	return tn.a + tn.b
}

func (tn *TwoInts) AddToParam(param int) int {
	return tn.a + tn.b + param
}
