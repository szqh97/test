package main
import "fmt"
func main() {
    p2  := Add32()
    fmt.Printf("Call Add32 fro 3 gives: %v\n", p2(3))
    TwoAdder := Adder(2)
    fmt.Printf("The result is :%v\n", TwoAdder(3))
}

func Add32()(func(b int) int){
    return func(b int) int {
        return b + 2
    }
}

func Adder(a int)(func(b int) int){
    return func (b int ) int {
        return a + b
    }
}
