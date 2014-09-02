package main
import (
    "fmt"
    "os"
    "bufio"
)

func main () {
    inputReader := bufio.NewReader(os.Stdin)
    fmt.Println("Prease enter your name:")
    input, err := inputReader.ReadString('\n')
    if err != nil {
        fmt.Println("There were error reading, exiting program.")
        return 
    }
    fmt.Printf("Your name is %s", input)

}
