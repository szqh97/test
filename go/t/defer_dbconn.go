package main
import "fmt"
func main(){
    doDBOperations()
}
func connectToDB(){
    fmt.Println("ok, connected to db")
}
func disconnectFromDB(){
    fmt.Println("ok, disconnected from db")
}

func doDBOperations(){
    connectToDB()
    fmt.Println("Defering the database disconnect.")
    defer disconnectFromDB()
    fmt.Println("Dogin some DB operations...")
    fmt.Println("Oops! some crash or network error ...")
    fmt.Println("Returning from function here~")
    return 
}
