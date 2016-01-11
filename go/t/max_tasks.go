package main
const (
    AvailableMemory = 10 << 20
    AverageMemeoryPerRequest = 10 << 10
    MAXREQS = AvailableMemory / AverageMemeoryPerRequest
)

var sem = make (chan int, MAXREQS)
type Request struct {
    a, b int
    replyc chan int
}

func process(r *Request) {

}

