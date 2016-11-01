package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	outputFile, outputError := os.OpenFile("/tmp/t.out.data", os.O_WRONLY|os.O_CREATE, 0666)
	if outputError != nil {
		fmt.Printf("An error accurred with opeing or create file")
		return
	}
	defer outputFile.Close()
	outputWriter := bufio.NewWriter(outputFile)
	outputWriter.WriteString("kkkkkkkk")
	out := "string hello"
	for i := 0; i < 10; i++ {
		outputWriter.WriteString(out)
	}
	outputWriter.Flush()
}
