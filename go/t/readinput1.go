package main
import "fmt"
var (
	firstName, lastName, s string
	i int
	f float32
	input = "56.12 / 532 / Go"
	format = "%f / %d / %s"
)
func main() {
	fmt.Println("Please enter your full name:")
	fmt.Scanln(&firstName, &lastName)
	fmt.Printf("hi %s %s", firstName, lastName)
	fmt.Scanf(input, format, &f, &i, &s)
	fmt.Println(f, i, s)

}
