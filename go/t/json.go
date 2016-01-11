package main
import (
    "fmt"
    "encoding/json"
    "os"
)
type Address struct {
    Type string
    City string
    Country string
}

type Vcard struct {
    FirstName string
    LastName string
    Address []*Address
    Remark string
}

func main() {
    pa := &Address{"private", "Aartselaar", "Belgium"}
    wa := &Address{"work", "Boom", "Belgium"}
    vc := Vcard{"Jan", "Kersschot", []*Address{pa, wa}, "none"}
    fmt.Println("%v: \n", vc)
    vc.Remark = "test"
    js, _ := json.Marshal(vc)
    fmt.Printf("Json format: %s", js)
    var f interface{}
    _ = json.Unmarshal([]byte(js), &f)
    fmt.Println(f)
    file, _ := os.OpenFile("vcard.json", os.O_CREATE|os.O_WRONLY, 0644)
    defer file.Close()
    enc := json.NewEncoder(file)
    err := enc.Encode(vc)
    if err != nil {
        fmt.Println("Error in encoding json")
    }
}
