package main
import (
    "time"
    "os"
    "fmt"
    "syscall"
)
func lock_and_write_pid(lock_file, pid_file string) (filehandler *os.File, err error) {
    filehandler, err = os.OpenFile(lock_file, os.O_RDWR|os.O_CREATE, 0644)
    if err != nil {
        fmt.Println("open file error")
        return nil, err
    }
    err = syscall.Flock(int(filehandler.Fd()), syscall.F_WRLCK)
    if err != nil {
        fmt.Println("lock file error:", err)
        return nil, err
    }

    return filehandler, nil

}
func f(s ...interface{}){
    fmt.Println(len([]interface{}(s)))
    fmt.Println(s)
}
func main(){
    f("x", "k")
    fh, err := lock_and_write_pid("./t.lock", "./t.pid")
    if err != nil {
        fmt.Println(err)
    }
    time.Sleep(time.Duration(time.Minute))
    fh.Close()

}
