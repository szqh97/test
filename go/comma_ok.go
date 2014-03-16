package main
import (
    "fmt"
    "strconv"
)

type Element interface{}
type List []Element

type Person struct{
    name string
    age int
}

func (p Person) String() string {
    return "(name: " + p.name + " - age: "  + strconv.Itoa(p.age) + "years)"
}

func main() {
    list := make (List, 3)
    list[0] = 1
    list[1] = "hello"
    list[2] = Person{"Dennis", 70}

    for index, element := range list {
        switch value := element.(type) {
        case int :
            fmt.Printf("list[%d] is an int and its value is %d\n", index, value)
        case string:
            fmt.Printf("list[%d] is an string and its value is %s\n", index, value)
        case Person:
            fmt.Printf("list[%d] is an Person and its value is %s\n", index, value)
        default:
            fmt.Printf("list[%d] is of a different type", index)
        }


        if value, ok := element.(int); ok {
            fmt.Printf("list[%d] is an int and its value is %d\n", index, value)
        } else if value, ok := element.(string); ok {
            fmt.Printf("list[%d] is an string and its value is %s\n", index, value)
        } else if value, ok := element.(Person); ok {
            fmt.Printf("list[%d] is an Person and its value is %s\n", index, value)
        } 

    }
}
