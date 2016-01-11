package main
import (
    "os"
    "text/template"
)
func main() {
    t := template.New("test")
    t = template.Must(t.Parse("{{with $3 := `hello`}}{{$3}}{{end}}!\n"))
    t.Execute(os.Stdout, nil)

    t2 := template.New("aa")
    t2 = template.Must(t2.Parse("{{with $x3 := `hola`}}{{$x3}}{{end}}\n"))
    t2.Execute(os.Stdout, nil)

    t3 := template.New("aa")
    t3 = template.Must(t3.Parse("{{with $x_1 = `hey`}}{{$x_1}}{{.}}{{$x_1}}{{end}}\n"))
    t3.Execute(os.Stdout, nil)
}
