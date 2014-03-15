package main
import "fmt"

type Vertex struct {
    X, Y int
}

var (
    p = Vertex{1,2}
    q = &Vertex{1,2}
    r = Vertex{X: 1}
    s = Vertex{}
)
func main(){
    a := new (Vertex)
    var t *Vertex = new (Vertex)
    fmt.Println(a)
    fmt.Println(t)
    fmt.Println(p, q, r, s)
}
