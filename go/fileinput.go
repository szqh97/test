package  main
import (
	"bufio"
	"fmt"
	"os"
)
func main() {
	inputFile, inputError := os.Open("big.go")
	if inputError != nil {
		fmt.Printf("An error ocurr while opening the file, does it exist!?")
		return
	}
	defer inputFile.Close()
	inputReader := bufio.NewReader(inputFile)
	for {
		inputString, err := inputReader.ReadString('\n')
		if err != nil {
			return
		}
		fmt.Printf("%s",inputString)

	}

}
