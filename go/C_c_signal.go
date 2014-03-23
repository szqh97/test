package main
import (
    "fmt"
    "os"
    "os/signal"
    "time"
)
func main(){
    c := make(chan os.Signal, 1)
   signal.Notify(c, os.Interrupt)
   go func(){
       for sig := range c{
           fmt.Printf("received Ctrl+c(%v)\n", sig)
           os.Exit(0)
       }
   }()
   for {
       time.Sleep(1000)
   }
}
