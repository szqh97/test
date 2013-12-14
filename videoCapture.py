#!/usr/bin/env python
# -*- coding: utf8 -*-
# Author: li_yun@vobile.cn
# Date: 2013-12-13 22:33:14

import re
import os
import web
import simplejson
import torndb
import uuid


urls = (
        "/videocapture", "VideoCapture",
        "/.*", "default",
        )

class default:
    def GET(self):
        return "xx"
    def POST(self):
        return "post"

class VideoCapture:
    def __init__(self):
        self.conn = None
        self.channel_id = None
        self.video_dir = ""
        self.snapshot_rate = 1
        self.height = -1
        self.weight = -1
        self.down_dir = ""
        self.down_prex = "http://192.168.1.249/"

    def load_conf(self):
        path = "/opt/rtfp/etc/live_box.conf"
        if not os.path.exists(path):
            print os.getcwd()
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
                if config.has_key("down_prex"):
                    d = config["down_prex"].strip()
                    if d is not None and len(d) != 0:
                        self.down_prex = d
                if config.has_key("video_dir"):
                    d = config["video_dir"].strip()
                    if d is not None and len(d) != 0:
                        self.video_dir= d
            except Exception, err:
                 pass

    def POST(self):
        self.load_conf()
        videofiles = []
        cmd = ""
        raw_data = web.data()
        post_data = simplejson.loads(raw_data)
        begint_ts = post_data.get('begin_ts')
        end_ts = post_data.get('end_ts')
        channel_uuid = post_data.get('channel_uuid')
        media_type = post_data.get('type')
        if channel_uuid != None:
            sql = "select id from videoSource where channel_uuid = %s" % channel_uuid
            try:
                conn = torndb.Connection('localhost', 'LiveBox', user='LiveBox', password='123')
                d_ids = conn.gt(sql)
                channel_id = str(d_ids['id'])
            except Exception, err:
                print "xx"
        else:
            print " channel uuid is null"

        allfiles = os.listdir(self.video_dir)
        re_parser = re.comple('\d+\.\d+\.\d+\.mp4', re.IGNORECASE)
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

            # 1. .. f_begint_ts .. begin_ts .. end_ts .. f_end_ts
            if f_begint_ts <= begin_ts and end_ts<= f_end_ts:
                video4split = f
                break
            # 2. .. f_begint_ts .. begin_ts .. f_end_ts ..
            if f_begint_ts <= begin_ts and f_end_ts < end_ts:
                video4split1 = f
                needmerge = True
            # 3. ... begin_ts .. f_begint_ts .. end_ts .. f_end_ts ..
            if begin_ts > f_begint_ts and f_begint_ts < end_ts:
                video4split2 = f
                needmerge = True
                break

        if needmerge == True:
            c = video4split1.split('.')[0]
            s = video4split1.split('.')[1]
            e = video4split2.split('.')[2]
            video4split = c + '.' + s + '.' + e + '.mp4'
            mergecmd = "ffmpeg -y -i %s -i %s -acodec copy -vcodec copy %s" % (video4split1, video4split2, video4split)
            ret = os.system(mergecmd)
            if ret != 0:
                print "merge video error!"

        f_begin_ts = int(video4split.split('.')[1])
        f_end_ts = int(video4split.split('.')[2])
        ss = begin_ts - f_begin_ts
        t = end_ts - begin_ts
        downurl = ""

        # request snap shot
        if media_type == 'snapshot':
            snapshots = "s-%%05d.jpg"
            snapshots = os.path.normpath(os.path.join(self.down_dir, snapshots))
            cmd = "ffmpeg -y -i %s -q:v 1 -ss %s -t %s -r %s -s %sx%s %s" \
                    % (video4split, ss, t, self.snapshot_rate, self.weight, self.height, snapshots)
            ret = os.sytem(cmd)
            if ret != 0:
                print "ffmegp error"
            snapshot_tgz = channel_id + "." + begin_ts + "." + end_ts + ".tgz"
            snapshot_tgz = os.path.normpath(os.path.join(self.down_dir, snapshot_tgz))
            cmd = "cd %s; tar cvzf %s s-*.jpg" % (self.down_dir, snapshot_tgz)
            ret = os.system(cmd)
            if ret != 0:
                print "tar cvzf error"
            cmd = "cd %s; rm s-*.jpg"
            ret = os.system(cmd)
            if ret != 0:
                pass
            downurl = self.donw_prex + '/' + snapshot_tgz.split(os.sep)[-1]

        # request video
        if media_type == 'video':
            outvideo = channel_id + '.' + begin_ts + '.' + end_ts + '.mp4'
            outvideo = os.path.normpath(os.path.join(self.down_dir, outvideo))
            cmd = "ffmpeg -y -i %s -acodec copy -vcodec copy -ss %s -t %s %s" % (f, ss, t, outvideo)
            ret = os.system(cmd)
            if ret != 0:
                print "ffmpeg split video serror"
            downurl = self.down_prex + '/' + outvideo.split(os.sep)[-1]
        requsetid = str(uuid.uuid4())
        response_info = {
                "requestId":requestId,
                "error":null,
                "resultUrlList":[downurl,]
                }
        resp = simplejson.dumps(response_info)
        return resp
        

if __name__ == '__main__':
    app = web.application(urls, globals())
    app.run()
