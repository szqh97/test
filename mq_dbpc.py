#!/usr/bin/env python
# -*- coding: utf8 -*-

# li_yun@vobile.cn 
# 2014-01-16 15:45:17
import httplib2
import simplejson
import time
import os

# CONFIG
user = "guest"
passwd = "guest"

detect_Q_url = "http://54.219.239.245/api/queues/%2F/tv_ads_detect_queue.dead"
query_Q_url = "http://54.219.239.245/api/queues/%2F/tv_ads_query_queue.dead"
airing_log_Q_url = "http://54.219.239.245/api/queues/%2F/tv_ads_airing_log_queue.dead"

dbpc_interval = "600"
dbpc_host = "192.168.1.146"
dbpc_port = "5800"
dbpc_service = "MQMonitor"

def get_Q_info(username, passwd, url):
    try:
        http = httplib2.Http()
        http.add_credentials(user, passwd)
        resp, content = http.request(url)
        if resp.status == 200:
            if simplejson.loads(content).has_key("messages"):
                return True
    except Exception, err:
        pass
    return False

def dbpc_fun():
    detect_Q_cmd = "./bin/heartbeat -h %s -p %s -s %s -c %s" % (dbpc_host, dbpc_port, dbpc_service, "detect_Q")
    query_Q_cmd = "./bin/heartbeat -h %s -p %s -s %s -c %s" % (dbpc_host, dbpc_port, dbpc_service, "query_Q")
    airing_log_Q_cmd = "./bin/heartbeat -h %s -p %s -s %s -c %s" % (dbpc_host, dbpc_port, dbpc_service, "airing_log_Q")
    if get_Q_info(user, passwd, detect_Q_url):
        os.system(detect_Q_cmd)

    if get_Q_info(user, passwd, query_Q_url):
        os.system(query_Q_cmd)

    if get_Q_info(user, passwd, detect_Q_url):
        os.system(airing_log_Q_cmd)


if __name__ == '__main__':
    while True:
        dbpc_fun()
        time.sleep(int(dbpc_interval))
