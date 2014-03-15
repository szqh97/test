package main

import "fmt"

func f(){
    for i:= 0; i < 10; i++{
        defer fmt.Println(i)
    }
    return
}

func main(){
    f()
}
