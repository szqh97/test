#!/usr/bin/env python
# -*- coding: utf8 -*-
# merge audio and video 
#  li_yun@163.com
#  2013-12-07 01:52:41

import os
import re
import signal
import pyinotify 
from pyinotify import WatchManager, Notifier, ProcessEvent, IN_MOVED_TO
g_quit = False
monitor_path = ''
config_parser = re.compile(
        "^[ \t]*([a-z0-9_]+)[ \t]*=[ \t]*([^#\n]+)[ \t]*(#.*)?$",
        re.IGNORECASE)
def signal_handler_for_tem(signum, frame):
    global g_quit 
    g_quit = True

def install_log(
def get_monitor_path():
    global monitor_path
    path = "./../etc/live_box.conf"
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
            if config.has_key("video_path"):
                d = config["video_path"].strip()
                print d
                if d is not None and len(d) != 0:
                    monitor_path = d 
        except Exception, err:
            print "open config file faile" 

class EventHandler(ProcessEvent):
    def __init__(self):
        self.avlist = {}
        
    def process_IN_MOVED_TO(self, event):
        # merge xxxx.a.mp4 and xxxx.v.mp4 to xxxx.mp4
        print "moved file to :" + event.path + event.name
        f = event.name
        channelid = f.split('.')[0]
        if not self.avlist.has_key(channelid):
            self.avlist.update({channelid:f})
            print "update avlist to :" + f
        else:
            outfile = os.path.normpath(os.path.join(event.path, f[0:-5] + "mp4"))
            print "out file is " + outfile

            try:
                tmp_f = self.avlist.pop(channelid)
            except KeyError:
                print "avlist has no value in key: "+ channelid

            if f.split('.')[-2] == 'a':
                f_a = os.path.normpath(os.path.join(event.path, f))
                print "f_a is :" + f_a
                f_v = os.path.normpath(os.path.join(event.path, tmp_f))
                print "f_v is :" + f_v
            elif f.split('.')[-2] == 'v':
                f_v = os.path.normpath(os.path.join(event.path, f))
                print "xf_v is :" + f_v
                f_a = os.path.normpath(os.path.join(event.path, tmp_f))
            cmd = "ffmpeg -i %s -i %s -codec copy %s ; rm -rf %s %s" % (f_a, f_v, outfile, f_a, f_v)
            print cmd
            ret = os.system(cmd)
            print "excute cmd result is " + str(ret)

    def process_default(self, event):
        print "default event is :" + event.path + event.name

def FSMonitor(path = '.'):
    signal.signal(signal.SIGTERM, signal_handler_for_tem)
    wm = WatchManager()
    eclist = pyinotify
    mask = eclist.IN_MOVED_TO
    notifier = Notifier(wm, EventHandler());
    print 'now starting monitor %s' % path
    wm.add_watch(path, mask, rec = True)

    while g_quit == False:
            notifier.process_events()
            if notifier.check_events():
                notifier.read_events()
            
if __name__ == '__main__':
    get_monitor_path()
    FSMonitor(monitor_path)
