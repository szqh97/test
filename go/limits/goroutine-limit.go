package main

import (
	"fmt"
	"time"
)

func run(task_id, sleeptime int, ch chan string) {
	time.Sleep(time.Duration(sleeptime) * time.Second)
	ch <- fmt.Sprintf("task id %d, sleep %d second", task_id, sleeptime)
	return
}

func main() {
	input := []int{1, 4, 3}
	ch := make(chan string)
	startTime := time.Now()
	fmt.Println("Multirun start")
	for i, sleeptime := range input {
		go run(i, sleeptime, ch)
	}

	for range input {
		fmt.Println(<-ch)

	}
	endtime := time.Now()
	fmt.Printf("finished, process time %v. Number of task is %d", endtime.Sub(startTime), len(input))

}
