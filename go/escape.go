package main

type data struct {
	name string
}

func f1() data {
	d := data{"abc"}
	return d
}

func f2() *data {
	d := data{"def"}
	return &d
}

func main() {
	d1 := f1()
	d2 := f2()
}
