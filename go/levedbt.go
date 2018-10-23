package main

import (
	"fmt"

	"github.com/syndtr/goleveldb/leveldb"
)

func main() {
	db, err := leveldb.OpenFile("./levedb.data", nil)
	defer db.Close()
	err = db.Put([]byte("key"), []byte("data"), nil)
	if err != nil {
		fmt.Println(err)

	}
	data, err := db.Get([]byte("TFSKKK"), nil)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Println(data == nil)

	fmt.Println("vim-go")
}
