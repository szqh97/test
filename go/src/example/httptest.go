package main

import (
	"net/http"
)

//type Hello struct {}
type String string
type Struct struct {
	Greeting string
	Punct    string
	Who      string
}

//func (h Hello) ServeHTTP (w http.ResponseWriter, r *http.Request) {
//    fmt.Fprint(w, "Hello")
//}

func main() {
	http.Handle("/string", String("I'm a frayed knot."))
	http.Handle("/struct", &Struct{"Hello", ":", "GOO"})
	http.ListenAndServe("localhost:4000", nil)
}
