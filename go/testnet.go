package main
import "net"
import "log"
func main(){
    tcpAddr, e := net.ResolveTCPAddr("tcp", "0.0.0.0:4150")
    if e != nil {
        log.Println(e)
    }
    log.Println(tcpAddr)


}
