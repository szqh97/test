package main
import (
    "fmt"
)

type Log struct {
    msg string
}

type Customer struct {
    Name string
    log *Log
}

func main() {
    c := new(Customer)
    c.Name = "Barak"
    c.log = new (Log)
    c.log.msg = "1- xxxx"

    c = &Customer{"Barak", &Log{"1-yes we can!"}}
    c.Log().Add("2 - After the world will be a better place!")
    fmt.Println(c.Log())
}

func (l *Log) Add(s string) {
    l.msg += "\n" 
    l.msg += s
}

func (l *Log) String() string {
    return l.msg
}

func (c *Customer) Log() *Log {
    return c.log
}
