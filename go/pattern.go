package main
import (
    "fmt"
    "regexp"
    "strconv"
)
func main() {
    searchIn := "John: 2578.34 William: 4567.23 Steve: 5632.18"
    pat := "[0-9]+.[0-9]+"

    f := func (s string) string {
        fmt.Printf("in lambda: %s\n", s)
        v, _ := strconv.ParseFloat(s, 32)
        return strconv.FormatFloat(v * 2, 'f', 2, 32)
    }
    if ok, _ := regexp.Match(pat, []byte(searchIn)); ok {
        fmt.Println("Match found!")
    }

    re, _ := regexp.Compile(pat)
    str := re.ReplaceAllString(searchIn, "##.#")
    fmt.Println(str)

    str2 := re.ReplaceAllStringFunc(searchIn, f)
    fmt.Println(str2)

    fmt.Println("xxxxxxxxxxxxxxxxx")
    
    fmt.Println(strconv.ParseFloat("43.44", 32))
}
