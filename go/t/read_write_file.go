package main
import (
	"fmt"
	"os"
	"io/ioutil"
)
func main () {
	inputFile := "rot13.go"
	outputFile := "rot13_copy.txt"
	buf, err := ioutil.ReadFile(inputFile)
	if err != nil {
		fmt.Fprintf(os.Stderr, "file error: %s\n", err)
		return
	}
	fmt.Printf("%s", string(buf))
	err = ioutil.WriteFile(outputFile, buf, 0x644)
	if err != nil {
		panic(err.Error())
	}

}

