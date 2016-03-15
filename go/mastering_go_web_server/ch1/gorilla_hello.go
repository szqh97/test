package main

import (
	"encoding/json"
	"fmt"
	"github.com/drone/routes"
	"github.com/gorilla/mux"
	"net/http"
)

type API struct {
	Message string "json:message"
}

func Hello(w http.ResponseWriter, r *http.Request) {
	urlParams := mux.Vars(r)
	name := urlParams["user"]
	HelloMessage := "Hello, " + name

	message := API{HelloMessage}
	output, err := json.Marshal(message)
	if err != nil {
		fmt.Println("Something went wrong")
	}
	fmt.Fprintf(w, string(output))
}

func HelloRoutes(w http.ResponseWriter, r *http.Request) {
	urlParams := r.URL.Query()
	name := urlParams.Get(":name")
	HelloMessage := "hello, " + name
	message := API{HelloMessage}
	output, err := json.Marshal(message)
	if err != nil {
		fmt.Println("Something went wrong")
	}
	fmt.Fprintf(w, string(output))
}
func main() {

	mux := routes.New()
	mux.Get("/api2/:name", HelloRoutes)
	/*
		gorillaroute := mux.NewRouter()
		gorillaroute.HandleFunc("/api/{user:[0-9]+}", Hello)
		http.Handle("/", gorillaroute)
	*/
	http.Handle("/", mux)
	http.ListenAndServe(":8080", nil)

}
