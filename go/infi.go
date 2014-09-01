package main 
import "fmt"
import "runtime"
type TT float64
func (t TT) String() string {
    return fmt.Sprintf("%v\n", t)
}
func main(){
    t := new(TT)
    fmt.Println(runtime.MemStats.Alloc)

}
