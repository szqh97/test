package main
import (
    "text/template"
    "fmt"
)

func main() {
    tOK := template.New("OK")
    template.Must(tOK.Parse("/* and a comment */ some static text: {{ .Name }}"))
    fmt.Println("The first one parsed OK.")
    fmt.Println("The next one outh to fail." )
    tErr := template.New("err_template")
    template.Must(tErr.Parse("Some static text {{ .Name }}"))
}
