package pidlock
import (
    "testing"
    "fmt"
)

func TestLock_write_pid_file(t *testing.T) {
    f := "./t.pid"
    fh, err := Lock_write_pid_file(f)
    if err != nil {
        fmt.Println("lock write pid file error")
    }
    fh.Close()
}
