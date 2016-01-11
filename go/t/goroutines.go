package main
import "fmt"
import "runtime"
import "time"
func f() {
    runtime.Gosched()
    fmt.Println("fxxxx")
}


func h() {
    runtime.Gosched()
    fmt.Println("hxxxx")
}

func main() {
    go f()
    go h()
    go f()
    go h()
    time.Sleep(55)
}
