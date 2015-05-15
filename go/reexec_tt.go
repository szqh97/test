package main
import (
	"github.com/docker/docker/pkg/reexec"
    "fmt"
)

func main(){
    fmt.Println("test")
	if reexec.Init() {
		return
	}

}

