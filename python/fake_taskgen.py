#!/usr/bin/env python
#
# ./fake_taskgen.py channels.pkl task
#
#
import simplejson
import cPickle
import sys
import uuid
import httplib2
import traceback


jobtracker_url = "http://192.168.50.52:8081/jobTracker/task/submit"
channels =[]
name_prex = "TEST_"
with file (sys.argv[1], 'r') as f:
    channels = cPickle.load(f)

#for i in xrange(100):
#    name = name_prex + str(i+1)
#    channel_uuid = str(uuid.uuid4())
#    channels.append({name:channel_uuid})

videocaptures=[
        "aaaaaaaaaaaaa",
        "BBBBBBBBBBBBB",
        "CCCCCCCCCCCC",
        "DDDDDDDDDDDD"
        ]

def gen_fake_task(taskf):
    task_info = None
    with file(taskf, 'r') as f:
        task_info = simplejson.load(f)
    i =0
    for channel in channels:
        try:
            task_info["requestId"] = str(uuid.uuid4())
            task_info["channel"]["name"] = channel.keys()[0]
            task_info["channel"]["uuid"] = channel.values()[0]
            task_info["channel"]["network"]["name"] = channel.keys()[0]
            task_info["videoManagerUrl"] = videocaptures[i/(100/len(videocaptures))]
            i+=1
        except Exception, e:
            print str(traceback.format_exc())
        post_data = simplejson.dumps(task_info)
        print post_data

        headers = {"Content-Type": "application/json"}
        try:
            http = httplib2.Http(disable_ssl_certificate_validation = True, timeout = 2)
            response = lambda: None
            xml_stream = ""
            response.status = 0
            response, xml_stream = http.request(jobtracker_url, "POST", headers = headers, body=post_data)
            if response and response.status == 200:
                print "success, xml_stream is: ", xml_stream
            else:
                print "failed, xml_stream is: ", xml_stream

        except Exception, e:
            print str(traceback.format_exc())


gen_fake_task(sys.argv[2])


