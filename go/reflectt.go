package main

import (
	"fmt"
	"reflect"
)

type Person struct {
	Name  string
	Age   int
	Phone int
}

var test []string

var user Person = Person{Name: "hell", Age: 11, Phone: 1234345}

func fields(typ reflect.Type) error {

	for i := 0; i < typ.NumField(); i++ {
		f := typ.Field(i)
		fmt.Println(f.PkgPath)

	}
	return nil
}

func main() {
	fields(reflect.TypeOf(user))
}
