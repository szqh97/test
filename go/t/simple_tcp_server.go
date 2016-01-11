package main
import (
    "flag"
    "net"
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
        checkError(err, "Accept:")
        go connectionHandler(conn)
    }
}
func initServer(hostAndPort string) *net.TCPListener {
    serverAddr, err := net.ResolveTCPAddr("tcp", hostAndPort)
    checkError(err, "Resolving address: port failed: '" + hostAndPort + "'")
    listener, err := net.ListenTCP("tcp", serverAddr)
    checkError(err, "ListenTCP: ")
    fmt.Println("Listening to: ", listener.Addr().String())
    return listener
}

func connectionHandler(conn net.Conn) {
    connFrom := conn.RemoteAddr().String()
    fmt.Println("Conncetion from: ", connFrom)
    sayHello(conn)
    for {
        var ibuf []byte = make([]byte, maxRead + 1)
        length, err := conn.Read(ibuf[0:maxRead])
        ibuf[maxRead] = 0
        switch err {
        case nil :
            handleMsg(length, err, ibuf)
        default:
            goto DISCONNECT
        }
    }
DISCONNECT:
    err := conn.Close()
    fmt.Println("closed closed conncetion. ", connFrom)
    checkError(err, "Close: ")
}

func sayHello(to net.Conn) {
    obuf := []byte{'L', 'e', 't', '\'', 's', ' ', 'G', 'O', '!', '\n'}
    wrote, err := to.Write(obuf)
    checkError(err, "Write: wrote " + string(wrote) + " bytes.")
}
func handleMsg(length int, err error, msg []byte){
    if length > 0{
        fmt.Println("<", length, ":")
        for i := 0; ; i ++ {
            if msg[i] == 0{
                break;
            }
            fmt.Printf("%c", msg[i])
        }
        fmt.Print(">")
    }
}

func checkError(error error, info string) {
    if error != nil {
        panic("Error: " + info + " " + error.Error())
    }
}

