package main

import (
	"encoding/json"
	"fmt"
	"net/http"
)

type User struct {
	Name  string `json:"name"`
	Email string `json:"email"`
	Id    int    `json:"int"`
}

func userRouter(w http.ResponseWriter, r *http.Request) {
	userRouter := User{}
	userRouter.Name = "Bill Smith"
	userRouter.Email = "bill.smith@example.com"
	userRouter.Id = 30

	output, _ := json.Marshal(userRouter)
	fmt.Println(string(output))
	fmt.Fprintf(w, string(output))

}

func main() {
	fmt.Println("Staring json server....")
	http.HandleFunc("/user", userRouter)
	http.ListenAndServe(":8080", nil)
}
