package main
import (
    _ "github.com/go-sql-driver/mysql"
    "database/sql"
    "encoding/json"
    "fmt"
    //"pidlock"
    //"time"
)
type network struct {
    Name string `json:"string"`
}

type channel_info struct {
    Channel_id int `json:"-"`
    Channel_uuid string `json:"uuid"`
    Channel_name string `json:"name"`
    Dma string `json:"dma"`
    network `json:"string"`
    //Network string
    TimeZone string `json:"timezone"`
    CaptureId string `json:"captureId"`
}
/*
        post_info = {
                "requestId": request_id, \
                "videoManagerUrl": videoManagerUrl, \
                "mainCapture": mainCapture, \
                "channel":{ \
                    "uuid": self.channel_uuid, \
                    "name": self.channel_name, \
                    "timezone": timezone, \
                    "network":{ \
                        "name": self.network},
                    "captureId": self.captureId, \
                    "dma": self.dma},\
                    "beginTimestamp": beginTimestamp, \
                    "endTimestamp": endTimestamp, \
                    "duration": duration, \
                    "taskDNA": self.taskDNA
                    }

*/
type task_info struct {
    BeginTimestamp uint64 `json:"beginTimestamp"`
    EndTimestamp uint64 `json:"endTimestamp"`
    BeginTimestampOfDNA uint64 `json:"beginTimestampOfDNA"`
    DownloadUrl string `json:"downloadUrl"`
}

type post_info struct {
    RequestId string `json:"requestId"`
    VideoManagerUrl string `json:"videoManagerUrl"`
    MainCapture string `json:"mainCapture"`
    EndTimestamp uint64 `json:"endTimestamp"`
    Duration uint64 `json:"duration"`
    TaskDNA []taskinfo `json:"taskDNA"`
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
