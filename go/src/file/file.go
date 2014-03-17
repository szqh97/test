package file
import (
    "fmt"
    "errors"
    "syscall"
)

type File struct {
    fd int // file descriptor number
    name string // file name at Open time
}

func newFile(fd int, name string) *File {
    if fd < 0 {
        return nil
    }

    return &File{fd, name}
}

var (
    Stdin = newFile(0, "/dev/stdin")
    Stdout = newFile(1, "/dev/stdout")
    stderr = newFile(2, "/dev/stderr")
)

func Open(name string, mod int, perm uint32) (file *File, err error) {
    r, e := syscall.Open(name, mod, perm)
    return newFile(r, name), e
}

func (file *File) Close() error {
    if file == nil {
        ss := fmt.Sprintf("%s is not exist", file.name)
        return errors.New(ss)
    }
    e := syscall.Close(file.fd)
    file.fd = -1
    return e
}

func (file *File) Read(b []byte) (ret int, err error) {
    if file == nil {
        ss := fmt.Sprintf("%s is not exist", file.name)
        return -1, errors.New(ss)
    }
    r, e := syscall.Read(file.fd, b)
    return int(r), e
}

func (file *File) Write (b []byte) (ret int, err error) {
    if file == nil {
        ss := fmt.Sprintf("%s is not exist", file.name)
        return -1, errors.New(ss)
    }
    r, e := syscall.Write(file.fd, b)
    return int(r), e
}

func (file *File) String() string {
    return file.name
}
