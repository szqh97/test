package main

import (
	"fmt"
)

type EmptyInterface interface {
}

type WithFuncInterface interface {
	Func()
}

type TestStruct struct {
	Member int
}

func (t *TestStruct) Func() {
	fmt.Printf("Haha\n")
}

func TestEmptyInterface(i EmptyInterface) {
	fmt.Printf("Interface: %v\n", i == nil)

}

func TestWithFuncInterface(i WithFuncInterface) {
	fmt.Printf("Func Interface: %v\n", i == nil)

}

func TestWithFuncStruct(i *TestStruct) {
	fmt.Printf("Struce Interface: %v\n", i == nil)

}

func main() {
	var test *TestStruct = nil
	TestEmptyInterface(test)
	TestWithFuncInterface(test)
	TestWithFuncStruct(test)
	test.Func()

	TestEmptyInterface(nil)    // <- True
	TestWithFuncInterface(nil) // <- True
	TestWithFuncStruct(nil)    // <- True

	fmt.Printf("%T\n", test)

}
