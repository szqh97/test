package main
import (
    "os"
    "fmt"
    "text/template"
)
type Person struct {
    Name string
}

func main() {
    t := template.New("hello")
    t, _ = t.Parse("hello {{.Name}}!")
    p := Person{Name: "mary"}
    if err := t.Execute(os.Stdout, p); err != nil {
        fmt.Println("There was an error:", err.Error())
    }
}
