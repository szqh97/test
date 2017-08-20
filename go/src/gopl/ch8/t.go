package main

import (
	"fmt"
	"net"
)

func main() {
	conn, err := net.Dial("tcp", "baidu.com:80")
	if err != nil {
		fmt.Println(err)
		return

	}
	conn.Write([]byte("GET HTTP 1.0\r\n"))
	fmt.Println()

}
