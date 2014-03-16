package main
import (
    "database/sql"
    "fmt"
    "runtime"
    _ "github.com/mattn/go-sqlite3"
)

func checkErr(err error) {
    if err != nil {
        fmt.Println("error occurred: ", err)
        panic(err)
    }
}

func dbinsert() {
    fmt.Println("insert ...")
    db, err := sql.Open("sqlite3", "./foo.db")
    checkErr(err)

    stmt, err := db.Prepare("insert into userinfo(username, departname, created) vaues(?, ?, ?)")
    checkErr(err)

    res, err := stmt.Exec("szqh97_", "aa", "2014-03-16")
    checkErr(err)

    id, err := res.LastInsertId()
    fmt.Println(id)

    defer db.Close()
}

func dbquery(){
    fmt.Println("in query...")
    db, err := sql.Open("sqlite3", "./foo.db")
    checkErr(err)

    rows, err := db.Query("select * from userinfo")
    checkErr(err)
    for rows.Next() {
        var uid int
        var username string
        var department string
        var created string
        err = rows.Scan(&uid, &username, &department, &created)
        checkErr(err)
        fmt.Println(uid, username, department, created)
    }
    defer db.Close()
}

func main() {
    runtime.GOMAXPROCS(4)
    go dbinsert()
    go dbinsert()
    go dbinsert()
    go dbinsert()
    go dbinsert()

}
