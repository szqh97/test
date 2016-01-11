package main
import (
    "encoding/gob"
    "log"
    "os"
)
type Address struct {
    Type, City, Country string
}
type VCard struct {
    FirstName string
    LastName string
    Address []*Address
    Remark string
}

func main() {
    pa := &Address{"private", "Aartselaar", "Belgium"}
    wa := &Address{"work", "Boom", "Belgium"}
    vc := VCard{"Jan", "Kersschot", []*Address{pa, wa}, "none"}
    file, _ := os.OpenFile("vcard.gob", os.O_CREATE|os.O_WRONLY, 0)
    defer file.Close()
    enc := gob.NewEncoder(file)
    if enc.Encode(vc) != nil {
        log.Println("Error in encoding gob")
    }
}
