package main
import (
    "os"
    "text/template"
)

func main() {
    tEmpty := template.New("template test")
    tEmpty = template.Must(tEmpty.Parse("Empty pipeline if daemo: {{ if `` }} will not print. {{end}}\n"))
    tEmpty.Execute(os.Stdout, nil)

    tWithValue := template.New("template test")
    tWithValue = template.Must(tWithValue.Parse("Non empty piple if damo: {{if `anything`}} will print. {{end}}\n"))
    tWithValue.Execute(os.Stdout, nil)

    tIfElse := template.New("template test")
    tIfElse = template.Must(tIfElse.Parse("if-else demo: {{ if `anything`}} print IF part . {{else}} print ELSE part.{{end}}\n"))
    tIfElse.Execute(os.Stdout, nil)
}
