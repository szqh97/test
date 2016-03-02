package main
import (
    "fmt"
    "os"
    "io"
    "bufio"
)
func main() {
    inputFile, inputErr := os.Open("/tmp/t") 
    if inputErr != nil {
        fmt.Println("Error occurred while open file")
        return
    }
    defer inputFile.Close()

    inputReader := bufio.NewReader(inputFile)
    for {
        inputString , readError := inputReader.ReadString('\n')
        if readError == io.EOF {
            return
        }
        fmt.Printf(" The input was %s\n", inputString)
    }
}
