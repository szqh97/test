package main
import "strings"
import "fmt"

func main(){
    dst := "you can yse"
    fmt.Print("xx ", strings.HasPrefix(dst, "you"), "\n")
    fmt.Print("xx ", strings.HasSuffix(dst, "yse"), "\n")
    fmt.Print("xx ", strings.Contains(dst, "can"), "\n")
    fmt.Print("xx ", strings.Index(dst, "can"), "\n")
    fmt.Print("xx ", strings.LastIndex(dst, "y"), "\n")
    fmt.Print("xx ", strings.Count(dst, "y"), "\n")
    fmt.Print("xx ", strings.Repeat(dst, 3), "\n")
    fmt.Print("xx ", strings.ToUpper(strings.Repeat(dst, 3)), "\n")
    fmt.Print("xx ", strings.Trim(dst, "y"), "\n")

}
