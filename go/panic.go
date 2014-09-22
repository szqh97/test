package main
import "fmt"
func main() {
    fmt.Println("Starting the program")
    defer fmt.Println("xxxxxxxxxx")
    panic("A server error occurred: stopping the program")
    defer func(){
     if recover() != nil {
         fmt.Printf("error")
     }
    }()
    fmt.Println("Ending>>>")
}
