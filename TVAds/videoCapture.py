#!/usr/bin/env python
# -*- coding: utf8 -*-
# Author: li_yun@vobile.cn
# Date: 2013-12-13 22:33:14

import re
import os
import sys
import logging
import logging.config
import web
import time
import uuid
import random 
import string
import simplejson
from web import webapi

sys.path.append(os.path.normpath(os.path.join(sys.path[0], "/opt/rtfp/bin")))

import torndb
urls = (
        "/videocapture", "VideoCapture",
        "/.*", "default",
        )

class default:
    def GET(self):
        return "default GET"
    def POST(self):
        return "default post"


def log(data):
    try:
        f = open("/var/tmp/videocapture.log", "a+")
        #f.write(str(web.ctx.method) + " " + str(web.ctx.path) + " : " + time.ctime() + "\n")
        f.write("\n" + time.asctime() + " - ")
        f.write(data)
        f.flush()
        f.close()
    except Exception, err:
        web.debug("write log file error: %s" % str(err))

class VideoCapture:
    def __init__(self):
        self.conn = None
        self.channel_id = None
        self.video_dir = ""
        self.snapshot_rate = '1'
        self.height = -1
        self.weight = -1
        self.down_dir = ""
        self.down_prex = "http://192.168.1.249"


    def load_conf(self):
        config_parser = re.compile(
                        "^[ \t]*([a-z0-9_]+)[ \t]*=[ \t]*([^#\n]+)[ \t]*(#.*)?$",
                                re.IGNORECASE)

        path = "/opt/rtfp/etc/live_box.conf"
        if not os.path.exists(path):
            log(os.getcwd())
            return
        else:
            try:
                config = {}
                for line in open(path):
                    mg = config_parser.match(line)
                    if mg != None:
                        config[mg.group(1)] = mg.group(2).rstrip(" \t").strip("\"")
                if config.has_key("snapshot_height"):
                    d = config["snapshot_height"].strip()
                    if d is not None and len(d) != 0:
                        self.height = d 
                if config.has_key("snapshot_weight"):
                    d = config["snapshot_weight"].strip()
                    if d is not None and len(d) != 0:
                        self.weight = d
                if config.has_key("snapshot_rate"):
                    d = config["snapshot_rate"].strip()
                    if d is not None and len(d) != 0:
                        self.snapshot_rate = d 
                if config.has_key("download_prex"):
                    d = config["download_prex"].strip()
                    if d is not None and len(d) != 0:
                        self.down_prex = d
                if config.has_key("video_path"):
                    d = config["video_path"].strip()
                    if d is not None and len(d) != 0:
                        self.video_dir= d
                if config.has_key("down_dir"):
                    d = config["down_dir"].strip()
                    if d is not None and len(d) != 0:
                        self.down_dir= d
                if config.has_key("max_reservetime"):
                    d = config["max_reservetime"].strip()
                    if d is not None and len(d) != 0:
                        self.max_reservetime = int(d)
            except Exception, err:
                web.debug("load conf error %s:" % str(err))


    def varify_params(self, requestId, begin_ts, end_ts, media_type, channel_uuid):
        if begin_ts >= end_ts:
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "begin_ts is larger or equal to end_ts"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "begin_ts is larger or equal to end_ts"), err_info
        
        ltime = int(time.time())
        if begin_ts < ltime - self.max_reservetime * 3600:
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "begin_ts is not in reserved time"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "begin_ts is not in reserved time"), err_info

        if media_type.lower() not in ('video', 'screenshot'):

            err_info = {"requestId":requestId, "error": {"code": 400, "message": "type is error"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "type is error"), err_info

        if channel_uuid is None:
            web.debug(" channel uuid is null")
            err_info = {"requestId":requestId, "error": {"code": 400, "message": "the channel uuid is not error"}}
            web.debug("error: %s"% str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "the channel uuid is not using"), err_info

    def get_channleid(self, requestId, channel_uuid):
        dbhost = ':'.join(("localhost", "3306"))
        dbname = "LiveBox"
        dbuser = "LiveBox"
        dbpass = "123"
        
        channel_id = ""
        if channel_uuid != None:
            sql = "select id from videoSource where channel_uuid = '%s' " % (channel_uuid,)
            conn = None
            try:
                conn = torndb.Connection(host=dbhost, database=dbname, user=dbuser, password=dbpass)
                d_ids = conn.get(sql)
                conn.close()
                if d_ids != None :
                    channel_id = str(d_ids['id'])
                else:
                    raise Exception( "channel uuid is null")
            except Exception, err:
                if conn is not None:
                    conn.close()
                err_info = {"requestId":requestId, "error": {"code": 400, "message": str(err)}}
                web.debug("error: %s"% str(err_info))
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "the channel uuid is not using"), err_info
        return channel_id

    def check_retried_request(self, requestId, begin_ts, end_ts, media_type, channel_id):

        if media_type.lower() == 'screenshot':
            snapshot_tgz = channel_id + "." + str(begin_ts) + "." + str(end_ts) + ".tgz"
            snapshot_tgz = os.path.normpath(os.path.join(self.down_dir, snapshot_tgz))
            downurl = self.down_prex + '/' + snapshot_tgz.split(os.sep)[-1]
            if os.path.exists(snapshot_tgz):
                response_info = {
                        "requestId":requestId,
                        "error":None,
                        "resultUrl":downurl
                        }
                #web.debug("resp is %s" % str(response_info))
                resp = simplejson.dumps(response_info)
                return (True, resp)
        elif media_type.lower() == 'video':
            outvideo = channel_id + "." + str(begin_ts) + "." + str(end_ts) + '.mp4'
            outvideo = os.path.normpath(os.path.join(self.down_dir, outvideo))
            downurl = self.down_prex + '/' + outvideo.split(os.sep)[-1]
            if os.path.exists(outvideo):
                response_info = {
                        "requestId":requestId,
                        "error":None,
                        "resultUrl":downurl
                        }
                #web.debug("resp is %s" % str(response_info))
                resp = simplejson.dumps(response_info)
                return (True, resp)
        return (False, "")

    def get_video4split(self, requestId, begin_ts, end_ts, channel_id):
        videofiles = []
        allfiles = os.listdir(self.video_dir)
        re_parser = re.compile('\d+\.\d+\.\d+\.mp4', re.IGNORECASE)
        for f in allfiles:
            if re_parser.match(f):
                videofiles.append(f)
        videofiles.sort()
        
        video4split = ""
        needmerge = False
        video4split1 = ""
        video4split2 = ""
        for f in videofiles:
            f_channel_id = f.split('.')[0]
            f_begin_ts = int(f.split('.')[1])
            f_end_ts = int(f.split('.')[2])

            # 1. .. f_begin_ts .. begin_ts .. end_ts .. f_end_ts
            if f_channel_id == channel_id and f_begin_ts <= begin_ts and end_ts<= f_end_ts:
                video4split = f
                break
            # 2. .. f_begin_ts .. begin_ts .. f_end_ts .. end_ts
            if f_channel_id == channel_id and f_begin_ts < begin_ts and f_end_ts < end_ts and begin_ts < f_end_ts :
                video4split1 = f
                needmerge = True
            # 3. ... begin_ts .. f_begin_ts .. end_ts .. f_end_ts ..
            if f_channel_id == channel_id and begin_ts < f_begin_ts and f_begin_ts < end_ts and end_ts < f_end_ts:
                video4split2 = f
                needmerge = True
                break

        if needmerge == True:
            if video4split1 == "" or video4split2 == "":
                err_info = {"requestId":requestId, "error": {"code": 400, "message": "the ts block is illegal"}}
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "the ts block is illegal"), err_info
            c = video4split1.split('.')[0]
            s = video4split1.split('.')[1]
            e = video4split2.split('.')[2]
            video4split = c + '.' + s + '.' + e + '.mp4'
            video4split = os.path.normpath(os.path.join(self.video_dir, video4split))
            video4split1 = os.path.normpath(os.path.join(self.video_dir, video4split1))
            video4split2 = os.path.normpath(os.path.join(self.video_dir, video4split2))
            #tmpf = os.tempnam()
            tmpf = "/tmp/file" + ''.join(random.sample(string.ascii_letters + string.digits, 4))
            try:
                with file(tmpf, 'w') as f:
                    f.write("file %s\n" % video4split1)
                    f.flush()
                    f.write("file %s\n" % video4split2)
                    f.flush()
            except Exception, err:
                web.debug( "write input file error: %s"% err)
                # raise exception herex

            mergecmd = "ffmpeg -y -f concat  -i %s -codec copy %s >/dev/null 2>&1" % (tmpf, video4split)
            ret = os.system(mergecmd)
            if ret != 0:
                err_info = {"requestId":requestId, "error": {"code": 503, "message": "concat videos failed!"}}
                web.debug("error: %s"% str(err_info))
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("503 Service Unavailable"), err_info
            cmd = "rm -f %s" % tmpf
            ret = os.system(cmd)
            if ret != 0:
                err_info = {"requestId":requestId, "error": {"code": 503, "message": "rm temp files failed!"}}
                web.debug("error: %s"% str(err_info))
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("503 Service Unavailable"), err_info
        else:
            if video4split != "":
                video4split = os.path.normpath(os.path.join(self.video_dir, video4split))
            else:
                web.debug("video4split: %s" % video4split)
                err_info = {"requestId":requestId, "error": {"code": 400, "message": "the beginTimestamp or endTimeStamp is illegal"}}
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("400 Bad Request", web.webapi.BadRequest, "the beginTimestamp or endTimeStamp is illegal"), err_info
        return (needmerge, video4split)

    def snapshot_video_split(self, requestId, begin_ts, end_ts, media_type,  video4split, outvideo):

        snapshot_tgz = outvideo[0:-3] + "tgz"
        ret = -1
        f_begin_ts = int(video4split.split(os.sep)[-1].split('.')[1])
        f_end_ts = int(video4split.split(os.sep)[-1].split('.')[2])
        ss = (begin_ts - f_begin_ts)/1000.0
        t = (end_ts - begin_ts)/1000.0
        if t > 30:
            self.snapshot_rate = str(0.5)
        downurl = ""

        cmd = "ffmpeg -y -i %s -acodec copy -vcodec copy -ss %s -t %s %s >/dev/null 2>&1" % (video4split, str(ss), str(t), outvideo)
        ret = os.system(cmd)
        if ret != 0:
            err_info = {"requestId":requestId, "error": {"code": 503, "message": "get video4split error!"}}
            web.debug("error: %s" % str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("503 Service Unavailable"), err_info

        # request snap shot
        if media_type.lower() == 'screenshot':
            prex = ''.join(random.sample(string.ascii_letters + string.digits, 4))
            snapshots = prex + "-%09d.jpg"
            jpgfiles = prex + "-*.jpg"
            snapshots = os.path.normpath(os.path.join(self.down_dir, snapshots))
            cmd = "ffmpeg -y -i %s -q:v 1 -r %s -s %sx%s %s >/dev/null 2>&1" % (outvideo, self.snapshot_rate, self.weight, self.height, snapshots)

            ret = os.system(cmd)
            if ret != 0:
                err_info = {"requestId":requestId, "error": {"code": 503, "message": "ffmpeg get screenshots failed!"}}
                web.debug("error: %s" % str(err_info))

                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("503 Service Unavailable"), err_info
            cmd = "cd %s; tar cvzf %s %s" % (self.down_dir, snapshot_tgz, jpgfiles)
            ret = os.system(cmd)
            if ret != 0:
                err_info = {"requestId":requestId, "error": {"code": 503, "message": "pack snapshots error!"}}
                web.debug("error: %s" % str(err_info))
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("503 Service Unavailable"), err_info
            cmd = "rm -f %s %s" % (os.path.normpath(os.path.join(self.down_dir, jpgfiles)), outvideo)
            ret = os.system(cmd)
            if ret != 0:
                err_info = {"requestId":requestId, "error": {"code": 503, "message": "delete temp files failed!"}}
                web.debug("error: %s" % str(err_info))
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("503 Service Unavailable"), err_info
            else:
                downurl = self.down_prex + '/' + snapshot_tgz.split(os.sep)[-1]

        # request video
        if media_type == 'video':
            if os.path.exists(outvideo): 
                downurl = self.down_prex + '/' + outvideo.split(os.sep)[-1]
            else:
                web.debug("outvideo not exists: %s" % outvideo)

        return (ret, downurl)

    def POST(self):
        self.load_conf()
        requestId = str(uuid.uuid4())
        channel_id = ""
        cmd = ""
        raw_data = web.data()
        post_data = simplejson.loads(raw_data)
        begin_ts = post_data.get('beginTimestamp')
        end_ts = post_data.get('endTimestamp')
        channel_uuid = post_data.get('channelUuid')
        media_type = post_data.get('type')
        self.varify_params(requestId, begin_ts, end_ts, media_type, channel_uuid)
        channel_id = self.get_channleid(requestId, channel_uuid)

        b, resp = self.check_retried_request(requestId, begin_ts, end_ts, media_type, channel_id)
        if b is True:
            return resp
            
        # if the shot file and mp4 required is exists, return them
        snapshot_tgz = ""
        outvideo = ""
        outvideo = channel_id + "." + str(begin_ts) + "." + str(end_ts) + '.mp4'
        outvideo = os.path.normpath(os.path.join(self.down_dir, outvideo))

        merged, video4split = self.get_video4split(requestId, begin_ts, end_ts, channel_id)

        ret, downurl = self.snapshot_video_split(requestId, begin_ts, end_ts, media_type, video4split, outvideo)
        if ret != 0:
            err_info = {"requestId":requestId, "error": {"code": 503, "message": "split video/screenshot error"}}
            web.debug("error: %s" % str(err_info))
            err_info = simplejson.dumps(err_info)
            raise web.webapi._status_code("503 Service Unavailable"), err_info

        # rm the merged file
        if merged is True:
            cmd = "rm -f %s" % video4split
            ret = os.system(cmd)
            if ret !=0:
                err_info = {"requestId":requestId, "error": {"code": 503, "message": "rm temp files error!"}}
                web.debug("error: %s" % str(err_info))
                err_info = simplejson.dumps(err_info)
                raise web.webapi._status_code("503 Service Unavailable"), err_info
        response_info = {
                "requestId":requestId,
                "error":None,
                "resultUrl":downurl
                }
        #web.debug("resp is %s" % str(response_info))
        resp = simplejson.dumps(response_info)
        return resp

#if __name__ == '__main__':
#    app = web.application(urls, globals())
#    app.run()
application = web.application(urls, globals()).wsgifunc()
