package main

import (
    _ "github.com/go-sql-driver/mysql"
    "database/sql"
    "fmt"
)

func checkErr(err error) {
    if err != nil {
        fmt.Println("error occurred: ", err)
        panic(err)
    }
}
func main() {

    db, err := sql.Open("mysql", "root:123@/test?charset=utf8")
    checkErr(err)

    // insert data
    stmt, err := db.Prepare("insert userinfo set username=?,departname=?, created=?")
    checkErr(err)

    res, err := stmt.Exec("szqh97", "development", "2014-03-16")
    checkErr(err)

    id, err := res.LastInsertId()
    checkErr(err)

    fmt.Println(id)

    // update 
    stmt, err = db.Prepare("update userinfo set username=? where uid=?")
    checkErr(err)

    res, err = stmt.Exec("szqh97_", id)
    checkErr(err)

    affect, err := res.RowsAffected()
    checkErr(err)

    fmt.Println(affect)

    // query data
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

    // delete date
    stmt, err = db.Prepare("delete from userinfo where uid=?")
    checkErr(err)

    res, err = stmt.Exec(3)
    checkErr(err)

    affect, err = res.RowsAffected()
    checkErr(err)
    
    fmt.Println(affect)
    
    defer db.Close()
    

}
