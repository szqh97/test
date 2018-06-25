package main

/*
#include <stdio.h>
#include <stdlib.h>
void print(char *str) {
	printf("%s\n", str);
}
*/

import "C"
import (
	"fmt"
	"unsafe"
)

func main() {
	fmt.Println("vim-go")

	s := "hello Go"
	cs := C.CString(s)
	C.print(cs)
	C.free(unsafe.Pointer(cs))

}
