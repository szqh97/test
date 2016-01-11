package main
import "fmt"
type Request struct {
    a, b int
    replyc chan int
}

type binOp func (a, b int) int

func run(op binOp, req *Request){
    req.replyc <- op(req.a, req.b)
}

func server(op binOp, service chan *Request, quit chan bool) {
    for {
        select {
        case req := <-service:
            go run(op, req)
        case <- quit:
            fmt.Println("quit ...")
            return
        }
    }
}

func startServer(op binOp) (service chan *Request, quit chan bool){
    service = make(chan *Request)
    quit = make(chan bool)
    go server(op, service, quit)
    return service, quit
}

func addition(a, b int)int {
    return a + b
}

func main() {
    adder, quit := startServer(addition)
    const N = 100
    var reqs [N]Request
    for i := 0; i < N; i++ {
        req := &reqs[i]
        req.a = i;
        req.b = i + N
        req.replyc = make(chan int)
        adder <- req
    }
    for i := N - 1; i >= 0; i-- {
        if <-reqs[i].replyc != N+2*i {
            fmt.Println("fail at", i)
        }else {
            fmt.Println("Request ", i, "is ok!")
        }
    }
    quit <- true
    fmt.Println("done")
}
