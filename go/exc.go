package main
import (
    "os"
    //"os/exec"
    "fmt"
)

func main() {
    env := os.Environ()
    procAttr := &os.ProcAttr{
        Env: env,
        Files: []*os.File{
            os.Stdin,
            os.Stdout,
            os.Stderr,
        },
    }
    pid, err := os.StartProcess("/bin/ls", []string{"ls", "-l"}, procAttr)
    if err != nil {
        fmt.Printf("Error %v Starting process!", err)
        os.Exit(1)
    }
    fmt.Printf("the process id is %v", pid)
}
