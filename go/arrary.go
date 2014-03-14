package main
import "fmt"
func main(){
    a := make([]int, 5)
    printSlice("a",a)
    b := make([]int, 0, 5)
    printSlice("b", b)
    c := b[:2]
    printSlice("c", c)
    d := c[2:5]
    printSlice("d", d)
    e := b[2:]
    printSlice("e", e)

    var z[]int
    fmt.Println(z, len(z), cap(z))
    if z == nil {
        fmt.Println("nil")
    }
    fmt.Println("----------------------")

    pow := make([]int, 10)
    for i := range pow{
        pow[i] = i << uint(1)
    }
    for _,value := range pow {
        fmt.Printf("%d\n", value)
    }
}
func printSlice(s string, x[]int){
    fmt.Printf("%s len=%d, cap=%d %v\n", s, len(x), cap(x), x)
}
