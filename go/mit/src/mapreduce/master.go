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
		}
	}()

	for {

		if len(mr.Workers) != 0 {
			break
		}
		time.Sleep(1 * time.Second)
	}
	for mapNum := 0; mapNum < mr.nMap; {
		for worker, status := range mr.WorkerStatus {
			fmt.Println("worker is ", worker, " status is ", status)
			if status == Registed || status == MapDone {
				jobargs := DoJobArgs{}
				jobargs.File = mr.file
				jobargs.Operation = Map
				jobargs.JobNumber = mapNum
				jobargs.NumOtherPhase = mr.nReduce

				fmt.Printf("MMMMMapnum is %d\n", mapNum)
				jobreply := DoJobReply{}

				ok := call(worker.address, "Worker.DoJob", jobargs, &jobreply)
				if ok != true {
					fmt.Errorf("call MapReduce.DoJob faile")
				} else {
					mr.WorkerStatus[worker] = MapDone
					mapNum++
					if mapNum >= mr.nMap {
						break
					}
				}

				fmt.Println("DOMAP result is :", jobreply.OK)

			}

		}
	}

	for reduceNum := 0; reduceNum < mr.nReduce; {
		for worker, status := range mr.WorkerStatus {
			fmt.Println("worker is ", worker, " status is ", status)
			if status == MapDone || status == ReduceDone {
				jobargs := DoJobArgs{}
				jobargs.File = mr.file
				jobargs.Operation = Reduce
				jobargs.JobNumber = reduceNum
				jobargs.NumOtherPhase = mr.nMap

				fmt.Printf("RRRRReduce is %d, nReduce is \n", reduceNum)
				jobreply := DoJobReply{}
				ok := call(worker.address, "Worker.DoJob", jobargs, &jobreply)
				fmt.Println("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", reduceNum)
				if ok != true {
					fmt.Errorf("call Worker.DoJob fail")
				} else {

					mr.WorkerStatus[worker] = ReduceDone
					reduceNum++
					if reduceNum >= mr.nReduce {
						break
					}
				}
			}
		}
	}

	return mr.KillWorkers()
}
