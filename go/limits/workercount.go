package main

import (
	"fmt"
	"time"
)

func Run(task_id, sleeptime, timeout int, ch chan string) {
	ch_run := make(chan string)
	go run(task_id, sleeptime, ch_run)
	select {
	case re := <-ch_run:
		ch <- re
	case <-time.After(time.Duration(timeout) * time.Second):
		re := fmt.Sprintf("task id %d, tieout ", task_id)
		ch <- re
	}
}
func run(task_id, sleeptime int, ch chan string) {
	time.Sleep(time.Duration(sleeptime) * time.Second)
	ch <- fmt.Sprintf("task id %d , sleep %d second", task_id, sleeptime)
	return
}

func main() {
	input := []int{3, 2, 1}
	timeout := 2
	chLimit := make(chan bool, 1)
	chs := make([]chan string, len(input))
	limitFunc := func(chLimit chan bool, ch chan string, task_id, sleeptime, timeout int) {
		Run(task_id, sleeptime, timeout, ch)
		<-chLimit
	}
	startTime := time.Now()
	fmt.Println("Multirun start")
	for i, sleeptime := range input {
		t := sleeptime
		chs[i] = make(chan string, 1)
		chLimit <- true
		go limitFunc(chLimit, chs[i], i, t, timeout)
	}

	for _, ch := range chs {
		fmt.Println(<-ch)

	}
	endTie := time.Now()

	fmt.Printf("Multi finished. process time %s, Number of task is :%d", endTie.Sub(startTime), len(input))

}
