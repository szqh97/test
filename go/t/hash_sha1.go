package main
import (
    "fmt"
    "crypto/sha1"
    "crypto/md5"
    "io"
    "log"
)

func main() {
    hasher := sha1.New()
    md5er := md5.New()
    io.WriteString(hasher, "test")
    io.WriteString(md5er, "test")
    m := []byte{}
    b := []byte{}
    fmt.Printf("Result: %x\n", hasher.Sum(b));
    fmt.Printf("Result: %d\n", hasher.Sum(b));
    fmt.Printf("md5: %x\n", md5er.Sum(m));
    fmt.Printf("md5: %d\n", md5er.Sum(m));
    hasher.Reset()
    data := []byte("We shall overcome~")
    n, err := hasher.Write(data)
    if n != len(data) || err != nil {
        log.Printf("has write error:%v/ %v", n, err)
    }
    checksum := hasher.Sum(b)
    fmt.Printf("Result: %x\n", checksum)
}
