package main
import (
    "fmt"
    "net"
    "io"
)

func main() {
    var (
        host = "www.apache.org"
        port = "80"
        remote = host + ":" + port
        msg string = "GET\n"
        data = make([]uint8, 4096)
        read = true
        count = 0
    )
    con, err := net.Dial("tcp", remote)
    defer con.Close()
    io.WriteString(con, msg)
    for read{
        count, err = con.Read(data)
        read = (err == nil)
        fmt.Printf(string(data[0:count]))
    }
    
}
