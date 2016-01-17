package mapreduce

import "container/list"
import "fmt"
import (
	"time"
)

type WorkerInfo struct {
	address string
	// You can add definitions here.
}

// Clean up all workers by sending a Shutdown RPC to each one of them Collect
// the number of jobs each work has performed.
func (mr *MapReduce) KillWorkers() *list.List {
	l := list.New()
	for _, w := range mr.Workers {
		DPrintf("DoWork: shutdown %s\n", w.address)
		args := &ShutdownArgs{}
		var reply ShutdownReply
		ok := call(w.address, "Worker.Shutdown", args, &reply)
		if ok == false {
			fmt.Printf("DoWork: RPC %s shutdown error\n", w.address)
		} else {
			l.PushBack(reply.Njobs)
		}
	}
	return l
}

func (mr *MapReduce) RunMaster() *list.List {
	// Your code here
	go func() {
		for {

			workerAddress := <-mr.registerChannel
			worker := &WorkerInfo{}
			worker.address = workerAddress
			mr.Workers[workerAddress] = worker
			mr.WorkerStatus[worker] = Registed
			fmt.Println("xxxxxxxx", mr.Workers)
		}
	}()

	for {
		fmt.Println("TTTTTTThe worker length is: ", len(mr.Workers))
		for mapNum := 0; mapNum < mr.nMap; mapNum++ {
			for worker, status := range mr.WorkerStatus {
				fmt.Println("worker is ", worker, " status is ", status)
				if status == Registed || status == MapDone {
					jobargs := DoJobArgs{}
					jobargs.File = mr.file
					jobargs.Operation = Map
					jobargs.JobNumber = mapNum
					jobargs.NumOtherPhase = mr.nReduce

					jobreply := DoJobReply{}

					ok := call(worker.address, "MapReduce.DoJob", jobargs, jobreply)
					if ok != true {
						fmt.Errorf("call MapReduce.DoJob faile")
					}

					fmt.Println("DOMAP result is :", jobreply.OK)

				}

			}
			time.Sleep(3 * time.Second)
		}

	}

	return mr.KillWorkers()
}
