package main
import "fmt"
type Human struct {
    name string
    age int
    phone string
}

type Student struct {
    Human
    school string
    loan float32
}

type Employee struct{
    Human
    company string
    money float32
}

func (h Human) SayHi() {
    fmt.Printf("Hi, I am %s you can call me on %s\n",  h.name, h.phone)
}

func (h Human) Sing(lyrics string) {
    fmt.Println("La la la , la , la .....", lyrics)
}

func (e Employee) SayHi() {
    fmt.Printf("Hi, I am %s, I work at %s, Call me on %s\n",
        e.name, e.company, e.phone)
}


type Men interface {
    SayHi()
    Sing(lyrics string)
}

func main() {
    mike := Student{Human{"Mike", 25, "222-222-xxx"}, "MIT", 0.00}
    paul:= Student{Human{"Paul", 25, "111-222-xxx"}, "MIT", 1000}
    sam := Student{Human{"Sam", 25, "333-222-xxx"}, "MIT", 4000}
    tom := Student{Human{"Tom", 25, "444-222-xxx"}, "MIT", 5000}

    var i Men
    i = mike
    fmt.Println("This is Mike, a student")
    i.SayHi()
    i.Sing("November rain")

    i = tom
    fmt.Println("this is tom, an employee")
    i.SayHi()
    i.Sing("Born to be world")

    fmt.Println("Let's use a slie of men and see what happend")
    x := make([]Men, 3)
    x[0], x[1], x[2] = paul, sam, tom
    for _, value := range x {
        value.SayHi()
    }
}
