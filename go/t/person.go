package main
import (
    "fmt"
    "strings"
)

type Person struct {
    firstName string
    lastName string
}

func upPerson (p *Person) {
    p.firstName = strings.ToUpper(p.firstName)
    p.lastName = strings.ToUpper(p.lastName)
}

func main() {
    var person1 Person
    person1.firstName = "Chirs"
    person1.lastName = "Woodward"
    upPerson(&person1)
    fmt.Printf("The name of the person is %s %s\n", person1.firstName, person1.lastName)

    pers2 := new(Person)
    pers2.firstName = "Chirs"
    pers2.lastName = "Woodward"
    (*pers2).lastName = "Woodward"
    upPerson(pers2)
    fmt.Printf("The name of the person is %s %s\n", pers2.firstName, pers2.lastName)

    pers3 := &Person{firstName:"Chirs", lastName:"Woodward"}
    upPerson(pers3)
    fmt.Printf("The name of the person is %s %s\n", pers3.firstName, pers3.lastName)



}
