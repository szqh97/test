package main
import (
	"fmt"
	"os"
	"bufio"
)
func main() {
	inputFile, _:= os.Open("rot13.go")
	defer inputFile.Close()
	inputReader := bufio.NewReader(inputFile)
	buf := make([]byte, 1024)
	_, err := inputReader.Read(buf)
	if err != nil {
		fmt.Println("read error")
	}
	fmt.Printf("%s", string(buf))
}
