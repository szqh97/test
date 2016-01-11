package main
import "fmt"
type IDuck interface {
    Quack()
    Walk()
}
func DuckDance(duck IDuck) {
    for i := 1; i <= 3; i++ {
        duck.Quack()
        duck.Walk()
    }
}
type Bird struct {
    // ...
}

func (b *Bird) Quack() {
    fmt.Println("I am quacking")
}
func (b *Bird) Walk() {
    fmt.Println("I am wakling")
}
func main () {
    b := new(Bird)
    //b := Bird{}
    DuckDance(&b)
}

