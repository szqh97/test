package main
import (
    "fmt"
    "io/ioutil"
    "os"
)

func main() {
    inputFile := "/tmp/t"
    outputFile := "/tmp/t.bk"
    buf, err := ioutil.ReadFile(inputFile)
    if err != nil {
        fmt.Fprintf(os.Stderr, "File Error: %s\n", err)
    }
    fmt.Println("%s\n", string(buf))
    err = ioutil.WriteFile(outputFile, buf, 0644)
    if err != nil {
        panic(err)
    }
}
