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
dbpc_host = "206.99.94.53"
dbpc_port = "5800"
dbpc_service = "tvads"
dbpc_component = "Dead_MQ"

def get_MQ_info(username, passwd, url):
    try:
        http = httplib2.Http()
        http.add_credentials(user, passwd)
        resp, content = http.request(url)
        if resp.status == 200:
            result_d = simplejson.loads(content)
            if result_d.has_key("messages") and int(result_d["messages"]) != 0:
                return False
    except Exception, err:
        pass
    return True

def dbpc_fun():
    detect_MQ_cmd = "./heartbeat -h %s -p %s -s %s -c %s" % (dbpc_host, dbpc_port, dbpc_service, dbpc_component)
    d = get_MQ_info(user, passwd, detect_Q_url)
    q = get_MQ_info(user, passwd, query_Q_url)
    a = get_MQ_info(user, passwd, airing_log_Q_url)
    if d and q and a:
        ret = os.system(detect_MQ_cmd)

if __name__ == '__main__':
    dbpc_fun()
