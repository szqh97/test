package main
import (
    "net/http"
    "io"
    "log"
)
const form = `<html>
                  <body>
                      <form action = "#" method="post" name="bar">
                          <input type="text" name="in"/>
                          <input type="submit" value="Submit"/>
                      </form>
                  </body>
              </html>`
func SimpleServer(w http.ResponseWriter, request *http.Request) {
    io.WriteString(w, "<h1>Hello world</b1>")
}
func FormServer(w http.ResponseWriter, request *http.Request) {
    w.Header().Set("Content-Type", "text/html")
    switch request.Method {
    case "GET":
        io.WriteString(w, form)
    case "POST":
        io.WriteString(w, request.FormValue("in"))
    }
}
 
type HandleFunc func (http.ResponseWriter, *http.Request)
func main() {
    http.HandleFunc("/test1", logPanics(SimpleServer))
    http.HandleFunc("/test2", logPanics(FormServer))
    err := http.ListenAndServe(":8088", nil)
    if err != nil {
        panic (err)
    }
}

func logPanics(function HandleFunc) HandleFunc {
    return func (writer http.ResponseWriter, request *http.Request) {
        defer func() {
            if x := recover(); x!= nil {
                log.Printf("[%v] caught panic: %v", request.RemoteAddr, x)
            }
        }()
        function(writer, request)
    }
}

