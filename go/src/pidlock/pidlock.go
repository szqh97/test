package pidlock
import (
    "syscall"
    "fmt"
    "os"
)

func Lock_write_pid_file(pid_file string) (f *os.File, err error) {
    lock_file, err := os.OpenFile(pid_file, os.O_RDWR|os.O_CREATE, 0644)
    if err != nil {
        return nil, err
    }
    err = syscall.Flock(int(lock_file.Fd()), syscall.LOCK_EX)
    if err != nil {
        return nil, err
    }
    lock_file.WriteString(fmt.Sprintf("%d\n", os.Getpid()))

    return lock_file, nil
}

