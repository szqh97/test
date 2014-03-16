package main
import (
    "fmt"
    "io"
    "os"
    "strconv"
    "time"
    "crypto/md5"
    "html/template"
    "net/http"
    "strings"
    "log"
)
func upload(w http.ResponseWriter, r *http.Request) {
    fmt.Println("method:", r.Method)
    if r.Method == "GET" {
        // GET METHOD
        curtime := time.Now().Unix()
        h := md5.New()
        io.WriteString(h, strconv.FormatInt(curtime, 10))
        token := fmt.Sprintf("%x", h.Sum(nil))
        t, _ := template.ParseFiles("upload.html")
        t.Execute(w, token)
    }else {
        // POST
        r.ParseMultipartForm(32 <<20)
        file, handler, err := r.FormFile("uploadfile")
        if err != nil{
            fmt.Println(err)
            return 
        }
        defer file.Close()
        fmt.Fprintf(w, "%v", handler.Header)
        f, err := os.OpenFile(handler.Filename, os.O_WRONLY|os.O_CREATE, 0666)
        if err != nil {
            fmt.Println(err)
            return 
        }
        defer f.Close()
        io.Copy(f, file)
    }
}
func sayhelloName(w http.ResponseWriter, r *http.Request) {
    r.ParseForm()
    fmt.Println(r.Form)
    fmt.Println("path", r.URL.Path)
    fmt.Println("scheme", r.URL.Scheme)
    fmt.Println(r.Form["url_long"])
    for k, v := range r.Form{
        fmt.Println("Key:", k)
        fmt.Println("val:", strings.Join(v,""))
    }
    fmt.Fprintf(w, "Hello szqh97")
}

func login(w http.ResponseWriter, r *http.Request) {
    fmt.Println("method: ", r.Method)
    if r.Method == "GET" {
        curtime := time.Now().Unix()
        h := md5.New()
        io.WriteString(h, strconv.FormatInt(curtime, 10))
        token := fmt.Sprintf("%x", h.Sum(nil))
        t, _ := template.ParseFiles("login.html")
        t.Execute(w, token)
    }else {
        r.ParseForm()
        token := r.Form.Get("token")
        if token != "" {
            fmt.Println("token is ok")
        }else {
            fmt.Println("token is error")
        }
        slice := []string{"apple", "pear", "banana"}
        log.Println(r.Form.Get("fruit"))
        for _, v := range slice{
            if v == r.Form.Get("fruit"){
                fmt.Println(v)
            }

        }
        log.Println("username: ", r.Form["username"])
        log.Println("password: ", r.Form["password"])
        template.HTMLEscape(w, []byte(r.Form.Get("username")))
    }
}

func main() {
    http.HandleFunc("/", sayhelloName)
    http.HandleFunc("/login", login)
    http.HandleFunc("/upload", upload)
    err := http.ListenAndServe(":9990", nil)
    if err != nil {
        log.Fatal("ListenAndServe: ", err)
    }

}
