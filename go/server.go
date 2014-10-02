package main
import (
    "fmt"
    "net"
)
func main() {
    fmt.Println("Starting the server ...")
    listener, err := net.Listen("tcp", "127.0.0.1:5000")
    if err != nil {
        fmt.Println("Error listening", err.Error())
        return
    }
    for {
        conn, err := listener.Accept()
        if err != nil {
            fmt.Println("Error acception", err.Error())
            return
        }
        go doServerStuff(conn)
    }
}

func doServerStuff(conn net.Conn){
    for {
        buf := make([]byte, 512)
        _, err := conn.Read(buf)
        if err != nil {
            fmt.Println("Error reading", err.Error())
            return
        }
        fmt.Printf( "Receive data: %v", string(buf))
    }
}
