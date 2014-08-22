package main
import "unicode"
import "fmt"
func main(){
    var ch int32 = 65
    fmt.Println(unicode.IsLetter(ch))
}
