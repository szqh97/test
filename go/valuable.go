package main
import "fmt"

type stockPosition struct {
    ticker string
    sharePrice float32
    count float32
}

func (s stockPosition) getValue() float32{
    return s.sharePrice * s.count
}

type  car struct {
    manufacture string
    model string
    price float32
}

func (c car) getValue() float32 {
    return c.price
}

type valuable interface {
    getValue() float32
}

func showValue(asset valuable){
    fmt.Printf("value of the asset is %f\n", asset.getValue())
}

func main() {
    var o valuable = stockPosition{"GOOG", 4556.3, 4}

    showValue(o)
    o = car{"Benz", "S260", 444523}
    showValue(o)
    if v, ok := o.(stockPosition); ok {
        fmt.Println(v)
    }
}
