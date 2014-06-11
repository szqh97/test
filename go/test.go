package main

import (
	"fmt"
    "crypto/md5"
    "io"
	"os"
    "runtime"
)

func main() {
	var m map[int]int
	fmt.Println(len(m))
	fmt.Println(m[4])
	if v, ok := m[4]; ok {
		fmt.Println("map has this key", v)
	} else {
		fmt.Println("map not has this key")
	}
	fmt.Println("x", os.Getpid())
	var a interface{}
	fmt.Println(fmt.Sprintf("xx", a))
    fmt.Println(float64(7/9.0))
    fmt.Println(runtime.Version())

    hostname,_ := os.Hostname()
    fmt.Println(hostname)
    h := md5.New()
    fmt.Println(h)


    io.WriteString(h, hostname)
    fmt.Println(h, hostname)
}
