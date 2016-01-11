package main
import (
    "file"
    "fmt"
    "os"
)

func main() { 
    hello := []byte("hello world\n")
    file.Stdout.Write(hello)
    file, err := file.Open("/does/not/exist", 0, 0)
    if file == nil {
        fmt.Println("can't open file: err= ", err)
        os.Exit(1)
    }
}

