package main
import "fmt"

type specialString string
var whatIsThis specialString = "hello"

func TypeSwitch() {
    testFunc := func(any interface {}) {
        switch v := any.(type) {
        case bool:
            fmt.Printf("any %v is a bool type\n", v)
        case int:
            fmt.Printf("any %v is a int type\n", v)
        case float32:
            fmt.Printf("any %v is a flot32 type\n", v)
        case string:
            fmt.Printf("any %v is a string type\n", v)
        case specialString:
            fmt.Printf("any %v is a specialString type\n", v)
        default:
            fmt.Println("unknown type !")
        }
    }
    testFunc(whatIsThis)

}

func main() {
    TypeSwitch()
}
