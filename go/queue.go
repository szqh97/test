package main

import (
	"fmt"
	"log"
	"time"

	"github.com/nsqio/go-diskqueue"
)

func NewAppLogger() diskqueue.AppLogFunc {
	return func(lvl diskqueue.LogLevel, f string, args ...interface{}) {
		log.Println(fmt.Sprintf(lvl.String()+": "+f, args...))
	}
}
func diskq() diskqueue.Interface {
	lg := NewAppLogger()
	return diskqueue.New("test-queue", "/tmp", 512, 0, 4, 2500, 2*time.Second, lg)

}
func main() {
	q := diskq()
	defer q.Close()

	q.Put([]byte("aa"))
	time.Sleep(10 * time.Second)
	q.Put([]byte("bb"))
	time.Sleep(10 * time.Second)
	q.Put([]byte("cc"))
	time.Sleep(10 * time.Second)
	q.Put([]byte("dd"))

	time.Sleep(10 * time.Second)
	q.Put([]byte("ee"))
	time.Sleep(10 * time.Second)
	q.Put([]byte("ff"))
	q.Put([]byte("gg"))
	q.Put([]byte("hh"))
	for i := 0; i < 400; i++ {

		s := <-q.ReadChan()
		fmt.Println(string(s))
	}

	fmt.Println("vim-go")
}
