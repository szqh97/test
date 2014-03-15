package main

import "fmt"

type person struct {
	name string
	age  int
}

func Older(p1, p2 person) (person, int) {

	if p1.age > p2.age {
		return p1, p1.age - p2.age
	}
	return p2, p2.age - p1.age
}

func main() {
	tom := person{"Tom", 18}
	var bob person
	bob.name, bob.age = "BOB", 25

	tb_Older, tb_diff := Older(tom, bob)
	fmt.Printf("Of %s and %s, %s is older by %d years",
		tom.name, bob.name, tb_Older.name, tb_diff)
}
