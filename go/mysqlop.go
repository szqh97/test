package main

import (
	"database/sql"
	"fmt"

	"fmt"

	_ "github.com/go-sQL-driver/mysql"
)

func checkErr(err error) {
	if err != nil {
		fmt.Println(err)
		panic(err)

	}

}
func main() {
	fmt.Println("vim-go")

	db, err := sql.Open("mysql", "test:123456@tcp(120.26.137.224:23306)/teamtalk")
	checkErr(err)

	rows, err := db.Query("select * from IMUser where id = 2396 limit 1")
	checkErr(err)

}
