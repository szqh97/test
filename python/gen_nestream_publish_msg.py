#!/usr/bin/env python
import sys
import httplib2
import json
storage = {}
storage["host"] = "10.198.159.221"
storage["path"] = "/storage/vddbair"

task_info = json.load(open(sys.argv[1], 'r'))
task_info["id"] = 1111
task_info["storage"] = storage
task_info["status"] = "submitted"
task_info["uuid"] = task_info["channel"]["uuid"] + "_" + str(task_info["endTimestamp"] / 1000000)
task_info["channel"]["videoUrl"] ="http://121.199.31.48:80/TVAds/videocapture"

s_payload = json.dumps(task_info)
with file(str(sys.argv[2]), 'w') as f:
    f.write(s_payload)
push_msg = {
        "properties":{}, 
        # FXIME tv_ads_detect_queue_cntv
        "routing_key":"tv_ads_detect_queue_cntv",
        "payload_encoding":"string",
        "payload":s_payload
        }

user = "guest"
passwd = "guest"


url = "http://192.168.1.110:15672/api/exchanges/%2f/job_tool_exchange/publish"
url = "http://54.193.192.104/api/exchanges/%2f/job_tool_exchange/publish"
http = httplib2.Http(timeout=15)
ret = lambda:None
xml_stream = ""
try:
    http.add_credentials(user, passwd)
    ret, xml_stream = http.request(url, 'POST', body=json.dumps(push_msg))
except:
    print "\n ----- error: ----\n"
    print json.dumps(push_msg)
    sys.exit(1)

if ret is None :
    print "\n ----- ret is None error: ----\n"
    print json.dumps(push_msg)
else:
    print ret, xml_stream
