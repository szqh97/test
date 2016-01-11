package main
import (
    "fmt"
    "os"
    "net"
    "bufio"
    "strings"
)

func main() {
    conn, err := net.Dial("tcp", "localhost:50000")
    if err != nil {
        fmt.Println("Error dialing", err.Error())
        return 
    }

    inputReader := bufio.NewReader(os.Stdin)
    fmt.Println("First, what's your name?")
    clientName, _ := inputReader.ReadString('\n')
    trimmedClient := strings.Trim(clientName, "\r\n")
    for {
        fmt.Println("What to send to the server? Type Q to quit.")
        input, _ := inputReader.ReadString('\n')
        trimmedInput := strings.Trim(input, "\r\n")
        if trimmedInput == "Q" {
            return 
        }
        _, err = conn.Write([]byte(trimmedClient + " says: " + trimmedInput))
    }
}
