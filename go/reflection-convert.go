package main

import (
	"fmt"
	"reflect"
)

type A struct {
	A int
	B int
	C string
	E string
}

type B struct {
	B int
	C string
	D int
	E string
}

func CopyStruct(src, dst interface{}) {

	sval := reflect.ValueOf(src).Elem()

	dval := reflect.ValueOf(dst).Elem()

	for i := 0; i < sval.NumField(); i++ {
		value := sval.Field(i)
		name := sval.Type().Field(i).Name

		dvalue := dval.FieldByName(name)
		if dvalue.IsValid() == false {
			continue
		}
		dvalue.Set(value)
	}

}

func main() {
	fmt.Println("vim-go")
	src := A{1, 1, "C", "E"}
	var dst B
	//dst := B{1, "C", 1, "E"}
	CopyStruct(src, dst)
}
