package main
import (
    "fmt"
    "flag"
    "os"
)

var (
    flagset = flag.NewFlagSet("nsqd", flag.ExitOnError)
    workid = flagset.String("config", "", "path to config file")
)
func main(){
    flagset.Parse(os.Args[1:])
    fmt.Printf("workid: %s", *workid)
}
