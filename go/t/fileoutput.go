package main
import (
    "os"
    "bufio"
    "fmt"
)
func main() {
    outputfile, outputError := os.OpenFile("output.dat", os.O_WRONLY|os.O_CREATE, 0666)
    if outputError != nil {
        fmt.Printf("An error occurred with file creation\n")
        return 
    }
    defer outputfile.Close()
    outputWriter := bufio.NewWriter(outputfile)
    outputstring := "hello world\n"

    for i := 0; i < 10; i++{
        outputWriter.WriteString(outputstring)
    }
    outputWriter.Flush()
}
