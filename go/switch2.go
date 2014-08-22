package main
import "fmt"
func main(){
    var num int = 7
    switch{
    case num < 0:
        fmt.Println("Number is negative")
    case num >0 && num < 10:
        fmt.Println("Number is between 0 and 10")
        fallthrough
    default:
        fmt.Println("Number is 10 or greater")
    }
}
