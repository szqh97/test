package main
 
import (
    "bytes"
    "fmt"
    "html/template"
    "net/http"
)
 
func WriteHttpResponse(w http.ResponseWriter, rb []byte) {
    w.Header().Set("Content-Type", "text/html; charset=utf-8")
    w.Write(rb)
}
 
func home(w http.ResponseWriter, r *http.Request) {
    if r.Method == "GET" {
        w.Header().Set("Content-Type", "text/html; charset=utf-8")
        t, _ := template.ParseFiles("home.html")
        var buf bytes.Buffer
        t.Execute(&buf, nil)
        WriteHttpResponse(w, buf.Bytes())
    }
}
 
func BeginServe() error {
    http.HandleFunc("/", home)
    err := http.ListenAndServe(":80", nil)
    return err
}
 
func main() {
    err := BeginServe()
    fmt.Println(err)
}
