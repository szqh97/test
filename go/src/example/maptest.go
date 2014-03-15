package main
import "fmt"
type Vertex struct {
    Lat, Long float64
}

var m = map[string]Vertex{
    "Bell Labs": Vertex{
        44, -8.66,
    },
    "Google": Vertex{
        45.6, 33,
    },
}
var k = map[string]Vertex{
    "AA": {1,3},
    "KK": {9,4},
}

func main() {

    k["AA"] = Vertex{8,999}
    delete (k, "BB")
    fmt.Println(m)
    fmt.Println(k)

}
