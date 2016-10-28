package main

import "fmt"
import "./person"

func main() {
	p := new(person.Person)
	p.SetFirstName("Eric")
	fmt.Println(p)
}
