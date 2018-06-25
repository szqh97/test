package main

import (
	"encoding/json"
	"fmt"
)

type TestObject struct {
	Name []byte `json:"name"`
	Nick []byte `json:"nick"`
}

func main() {
	to := TestObject{
		Name: []byte("hello"),
		Nick: []byte("Kakak"),
	}

	out, err := json.Marshal(to)
	if err != nil {
		fmt.Println(err)

	}
	fmt.Println(string(out))
}
