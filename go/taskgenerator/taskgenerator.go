package main
import (
    _ "github.com/go-sql-driver/mysql"
    "database/sql"
    "fmt"
    //"pidlock"
    //"time"
)

type channel_info struct {
    Channel_id int
    Channel_uuid string
    Channel_name string
    Dma string
    Network string
}


func checkError(err error) {
    if err != nil {
        fmt.Println("xx", err)
        panic (err)
    }
}

func GetChannelInfos(dbinfo string) (infos []channel_info, err error) {
    db, err := sql.Open("mysql", dbinfo)
    checkError(err)

    // query infos from db
    // FIXME use isnull to set a default value to avoid type convert
    rows, err := db.Query("select id, channel_uuid, if(isnull(channel_name), 'null', channel_name) as channel_name, if(isnull(dma), 'null', dma) as dma, if(isnull(network), 'null', network) as network from videoSource where is_using = 'true' ")
    checkError(err)

    for rows.Next() {
        var ch channel_info
        err = rows.Scan(&(ch.Channel_id), &(ch.Channel_uuid), &(ch.Channel_name), &(ch.Dma), &(ch.Network))
        fmt.Println(ch)
        checkError(err)
        infos =append(infos, ch)
    }

    return infos, nil
}

func main() {
    dbinfo := "root:123@tcp(localhost:3306)/LiveBox?charset=utf8"
    infos, err :=  GetChannelInfos(dbinfo)
    if err != nil {
        fmt.Println("errrrr")
    }
    fmt.Println(infos)
}
