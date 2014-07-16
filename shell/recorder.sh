#!/bin/sh

start_ts=$(date +%s) 
mplayer -dumpstream http://122.192.67.86:8088/ts300  -dumpfile ${start_ts}.mp4 >${start_ts}.mp4.log 2>&1 &
while true
do 
    if [ "$(date +%s)" -ge "$((start_ts+4*3600))" ]
    then 
        start_ts=$(date +%s) 
        ps -ef|grep "mplayer -dumpstream http://122.192.67.86:8088/t" |grep -v grep |awk '{print $2}'|xargs kill -9
        mplayer -dumpstream http://122.192.67.86:8088/ts300  -dumpfile ${start_ts}.mp4 >${start_ts}.mp4.log 2>&1 &
    else
        sleep 30
    fi 
done
