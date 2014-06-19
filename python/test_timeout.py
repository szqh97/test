#!/usr/bin/env python
import httplib2
import socket
import json
import traceback
http = httplib2.Http(timeout = 5)
url = "http://192.168.1.243/kk"
ss ={'test':'test'}
headers = {"Content-Type": "application/json"}
post_data= json.dumps(ss)

try:
    response, xml_stream = http.request(url, "POST", headers = headers, body=post_data)
except httplib2.timeout, err:
    print str(traceback.format_exc())
    print "timeoout", str(err)

