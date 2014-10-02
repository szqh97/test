package main
import (
    "flag"
    "net"
    "os"
    "fmt"
)
const maxRead = 25

func main() {
    flag.Parse()
    if flag.NArg() != 2 {
        panic ("Usage: host port")
    }
    hostAndPort := fmt.Sprintf("%s:%s", flag.Arg(0), flag.Arg(1))
    listener := initServer(hostAndPort)
    for {
        conn, err := listener.Accept()
        check
    }
}
func initServer(hostAndPort string) *net.TCPListener {
    serverAddr, err := net.ResolveTCPAddr("tcp", hostAndPort)
    checkError(err, "Resolving address: port failed: '" + hostAndPort + "'")
    listener, err := net.ListenTCP("tcp", serverAddr)
    checkError(err, "ListenTCP: ")
    println("Listening to: ", listener.Addr().String())
    return listener
}

func connectionHandler(conn net.Conn) {
    connFrom := conn.RemoteAddr().String()
    println("Conncetion from: ", connFrom0
    sayHello(conn)
    for {
        var ibuf []byte = make([]byte, maxRead + 1)
        length, err := conn.Read(ibuf[0:maxRead])
        ibuf[maxRead] = 0
        switch err {
        case nil :
            handleMsg(length, err, ibuf)
        case os.EAGAIN:
            continue
        default:
            goto DISCONNECT
        }
    }
DISCONNECT:
    err := conn.Close()
    println("closed closed conncetion. ", connFrom)
    checkError(err, "Close:")

}

