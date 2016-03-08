package main

import (
    "fmt"
    "time"
)

func main() {
    fmt.Println("In main()")
    go longwait()
    go shortwait()
    fmt.Println("About to sleep in main()")
    time.Sleep(10*1e9)
    fmt.Println("At the end of main()")
}

func longwait(){
    fmt.Println("Beginning longwait()")
    time.Sleep(5 * 1e9)
    fmt.Println("End of longwait()")
}

func shortwait(){
    fmt.Println("Beginning shortwait()")
    time.Sleep(2* 1e9)
    fmt.Println("End of shortwait()")
}
