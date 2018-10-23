package main

import (
	"fmt"
	"regexp"
)

func main() {
	fmt.Println("vim-go")
	reg := regexp.MustCompile(`([\w\.]{18})(\.(gif|jpeg|jpg|png|js|css|json))?(_(\d+)x(\d+))?$`)
	name := []byte("T3D_hTBTZT1RXrhCrK.jpg")
	fmt.Println(reg.Match(name))
}
