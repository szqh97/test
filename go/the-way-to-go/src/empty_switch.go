package main

import "fmt"

type specialString string

var whatIsTish specialString = "hello"

func TypeSwitch() {
	testFunc := func(any interface{}) {
		switch v := any.(type) {
		case bool:
			fmt.Printf("any %v is a bool type", v)
		case int:
			fmt.Printf("any %v is a int type", v)
		case float32:
			fmt.Printf("any %v is a float32 type", v)
		case string:
			fmt.Printf("any %v is a string type", v)
		case specialString:
			fmt.Printf("any %v is a specialString type", v)
		default:
			fmt.Printf("unknown type~!")
		}
	}
	testFunc(whatIsTish)
}
func main() {
	fmt.Println("vim-go")
	TypeSwitch()
}
