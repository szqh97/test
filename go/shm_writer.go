package main

import "C"
import (
	"fmt"
	"unsafe"
)

const SHM_NAME = "my_shm"
const SHM_SIZE = 4 * 1000 * 1000 * 1000

type MyDat struct {
	Col1 int
	Col2 int
	Col3 int
}

func main() {

	if err != nil {
		fmt.Println(err)
		return
	}

}
