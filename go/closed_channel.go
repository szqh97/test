package main
import (
    "fmt"
    "sync"
    "time"
)


func main() {
    const n = 1
    finish := make(chan bool)
    var done sync.WaitGroup
    for i := 0; i < n; i++ {
        done.Add(1)
        go func(){
            select {
            case <- time.After(1 * time.Second):
            case <- finish:
            }
            done.Done()
        }()
    }
    t0 := time.Now()
    close(finish)
    done.Wait()
    fmt.Printf("waited %v for goroutine to stop\n", time.Since(t0))
}
