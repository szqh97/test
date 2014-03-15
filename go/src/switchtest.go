package main
import (
    "fmt"
    "runtime"
    "time"
)

func main() {
    fmt.Print("Go runs on ")
    switch os := runtime.GOOS; os {
    case "darwin":
        fmt.Println("OS x.")
    case "linux":
        fmt.Println("Linux.")
    default:
        // freebsd, openbsd
        //plan9 windows ...
        fmt.Printf("%s", os)
    }

    fmt.Println("xxxxxxxxxxxxxxxxxxxxxxxxxx")
    fmt.Println("When's Saturday?")
    today := time.Now().Weekday()
    switch time.Saturday {
    case today + 0:
        fmt.Println("Today")
    case today + 1:
        fmt.Println("Tommorrow")
    case today + 2:
        fmt.Println("In two days")
    default:
        fmt.Println("Too far away")
    }
    fmt.Println("xxxxxxxxxxxxxxxxxxxxxxxxxx")
    t := time.Now()
    switch {
    case t.Hour() < 2:
        fmt.Println("Good morning")

    case t.Hour() < 17:
        fmt.Println("Good Afternoon")
    default:
        fmt.Println("Good evening")
    }
}
