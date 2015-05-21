package main

import (
    "fmt"
    "github.com/gorilla/mux"
    "net/http"
    "time"
)

func rootHandler(w http.ResponseWriter, r *http.Request) {
    time.Sleep(5 * time.Second)
    fmt.Fprintf(w, "Hello!")
}

func main() {
    mux := mux.NewRouter()
    mux.HandleFunc("/", rootHandler)

    muxWithMiddlewares := http.TimeoutHandler(mux, time.Second*39, "Timeout!")

    http.ListenAndServe(":18080", muxWithMiddlewares)
}
