#!/usr/bin/env python
# -*- coding: utf8 -*-
# Author: li_yun@vobile.cn
# Date:  2013-12-09 10:08:05

import os
import re
import time
import uuid
import torndb
import struct
import logging
import logging.config
import httplib2
import threading
import traceback
import simplejson
import collections
from Live.lock import lock_and_write_pid
import ConfigParser
from apscheduler.scheduler import Scheduler
import xml.dom.minidom
from xml.dom.minidom import parse, parseString


logger = logging
config_parser = re.compile(
        "^[ \t]*([a-z0-9_]+)[ \t]*=[ \t]*([^#\n]+)[ \t]*(#.*)?$",
        re.IGNORECASE)

lock_file = './var/run/taskgenerator.lock'
pid_file = './var/run/taskgenerator.pid'

V_DNA_VERSION = 2
CB_LEN = 24
DNA_FRAME_LEN = 40
DNA_HEADER_LEN = 48
def install_logger():
    global logger
    logger.config.fileConfig('./etc/logging.conf')
    logger = logger.getLogger('taskgenerator')


class task_generator(threading.Thread):
    """ 
    generate task for TV Ads Job tracker
    """
    def __init__(self, channel_id, channel_uuid, channel_name, dma, network):
        threading.Thread.__init__(self)
        self.task_len = 6 #the task cycle time (hour)
        self.redunt_time = 60 #the redundancy time (second)
        self.shotfiles = []
        self.dnafiles = []
        self.dna_dir = '/opt/rtfp/var/cache/dna_dir'
        self.ltime = None
        self.channel_id = channel_id 
        self.channel_uuid = channel_uuid
        self.channel_name = channel_name
        self.dma = dma 
        self.network = network
        self.dna_len= 0
        self.dna_begin_ts = -1
        self.dna_end_ts = -1
        self.taskDNA=[]
        self.download_prex = ""
        self.down_dir = '/opt/rtfp/var/dowload'
        self.captureId = "1"
        self.task_duration =3600 
        self.jobtrackerurl = ""
        self.vmurl = ""

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
                if config.has_key("down_dir"):
                    d = config["down_dir"].strip()
                    if d is not None and len(d) != 0:
                        self.down_dir = d 
                if config.has_key("captureId"):
                    d = config["captureId"].strip()
                    if d is not None and len(d) != 0:
                        self.captureId = int(d)
                if config.has_key("download_prex"):
                    d = config["download_prex"].strip()
                    if d is not None and len(d) != 0:
                        self.download_prex = d
                if config.has_key("redunt_time"):
                    d = config["redunt_time"].strip()
                    if d is not None and len(d) != 0:
                        self.redunt_time = int(d)
                if config.has_key("dna_path"):
                    d = config["dna_path"].strip()
                    if d is not None and len(d) != 0:
                        self.dna_dir = d
                if config.has_key("jobtracker_url"):
                    d = config["jobtracker_url"].strip()
                    if d is not None and len(d) != 0:
                        self.jobtrackerurl = d
                if config.has_key("videoManagerUrl"):
                    d = config["videoManagerUrl"].strip()
                    if d is not None and len(d) != 0:
                        self.vmurl = d
                if config.has_key("captureId"):
                    d = config["captureId"].strip()
                    if d is not None and len(d) != 0:
                        self.captureId = d
            except Exception, err:
                logger.error("open config file failed: %s", err)


    def merge_dna(self, dnaf_pair):
        if len(dnaf_pair) != 1 :
            logger.error("dnaf_pair is error")
            raise Exception("dna_pair is error")
        prev_dnaf = dnaf_pair.keys()[0]
        curr_dnaf = dnaf_pair.values()[0]
        if os.path.exists(prev_dnaf) is not True or os.path.exists(curr_dnaf) is not True:
            logger.error("%s or %s not exists", prev_dnaf, curr_dnaf)
            raise Exception ("dna file not exists")

        channel_id = prev_dnaf.split(os.sep)[-1].split('.')[0]

        pfd = file(prev_dnaf, 'r')
        cfd = file(curr_dnaf, 'r')
        h = cfd.read(CB_LEN)
        h = struct.unpack('4iq', h)
        c_begin_ts = h[4]
        cfd.seek(-(CB_LEN + DNA_FRAME_LEN), 2)
        dna = cfd.read(DNA_FRAME_LEN)
        last_ts = struct.unpack('I', dna[0:4])[0]
        new_end_ts = c_begin_ts + last_ts

        # get end td
        pfd.seek(-(CB_LEN + DNA_FRAME_LEN), 2)
        dna = pfd.read(DNA_FRAME_LEN)
        end_ts = struct.unpack('I', dna[0:4])[0]
        tmp_start_ts = end_ts - self.redunt_time * 1000

        pfd.seek(-(CB_LEN + DNA_FRAME_LEN), 2);
        dna = pfd.read(DNA_FRAME_LEN)
        last_dnats = struct.unpack('I', dna[0:4])[0]

        pfd.seek(CB_LEN)
        dna_header = pfd.read(DNA_HEADER_LEN)
        h = pfd.read(CB_LEN)
        h = struct.unpack('4iq', h)
        begin_ts = h[4]
        dt = c_begin_ts - begin_ts - last_dnats

        ts1 = ts2 = 0
        off_ts = 0
        new_start_ts = 0
        newfd = lambda: None
        new_dna_file = ""
        buff = ""
        while h[2] != 0:
            dnasbuff = pfd.read(h[2])
            while len(dnasbuff) != 0:
                dna = dnasbuff[0:DNA_FRAME_LEN]
                dnasbuff = dnasbuff[DNA_FRAME_LEN:]
                ts1 = struct.unpack('I', dna[0:4])[0]
                if ts1 <= tmp_start_ts:
                    # drop dna whose ts is smaller than tmp_start_ts
                    ts2 = ts1
                else:
                    # get the offset ts
                    if off_ts == 0:
                        off_ts = ts2 + dt
                        new_start_ts = begin_ts + off_ts 
                        if self.dna_begin_ts == -1:
                            self.dna_begin_ts = new_start_ts
                        self.dna_end_ts = last_ts + c_begin_ts
                        new_dna_file = "".join((channel_id, ".", str(new_start_ts), ".", str(self.dna_end_ts), ".vdna"))
                        new_dna_file = os.path.normpath(os.path.join(self.down_dir, new_dna_file))
                        logger.info("new dna file: %s", new_dna_file)
                        media_len = end_ts - off_ts + last_ts
                        media_len = int(round((media_len + 500) / 1000))
                        media_len = struct.pack('I', media_len)
                        dna_header = dna_header[0:4] + media_len + dna_header[8:]
                        newfd = file(new_dna_file, 'w')
                        newfd.write(dna_header)
                        newfd.flush()

                    nts = ts1 - ts2 
                    if nts >= 0:
                        off_ts = nts
                        nts = struct.pack('I', nts)
                        dna = nts + dna[4:]
                        buff += dna
                    else:
                        logger.info("timestamp error")
                if len(buff) >= 8192:
                    newfd.write(buff[0:8192])
                    newfd.flush()
                    buff = buff[8192:]
            h = pfd.read(CB_LEN)
            h = struct.unpack('4iq', h)
        #off_ts = nts

        # merge curr dna file
        cfd.seek(CB_LEN + DNA_HEADER_LEN )
        h = cfd.read(CB_LEN)
        h = struct.unpack('4iq', h)
        while h[2] != 0:
            dnasbuff = cfd.read(h[2])
            while len(dnasbuff) != 0:
                dna =  dnasbuff[0:DNA_FRAME_LEN]
                dnasbuff = dnasbuff[DNA_FRAME_LEN:]
                ts = struct.unpack('I', dna[0:4])[0]
                ts += off_ts 
                ts = struct.pack('I', ts)
                dna = ts + dna[4:]
                buff += dna
            if len(buff) >= 8192:
                newfd.write(buff[0:8192])
                newfd.flush()
                buff = buff[8192:]
            h = cfd.read(CB_LEN)
            h = struct.unpack('4iq', h)

        if len(buff) > 0:
            newfd.write(buff)
            newfd.flush()
            del buff

        newfd.close()
        pfd.close()
        cfd.close()
        return (0, new_dna_file)

    def dna_shot_merge(self, dna_shot_pairs):

        n_dna_shot_pairs = {}
        vdnafile = ""
        for shotfile, dnafiles in dna_shot_pairs.iteritems():

            logger.info("dnafiles prev:%s, curr:%s shotfile: %s", dnafiles.keys()[0].split(os.sep)[-1], \
                    dnafiles.values()[0].split(os.sep)[-1], shotfile.split(os.sep)[-1])
            try:
                ret, vdnafile= self.merge_dna(dnafiles)
            except Exception, err:
                logger.error("merge_dna error: %s", str(traceback.format_exc()))

            if ret != 0 or vdnafile == "":
                logger.error("merge dna file failed!")
                return (-1, None)

            # shot file 
            if not os.path.exists(shotfile):
                logger.fatal(" shot file %s not exist", shotfile)
                return (-1, None)
            sf = shotfile.split(os.sep)[-1]
            sf = sf[0:-3] + "inf"
            newshotfile = os.path.normpath(os.path.join(self.down_dir, sf))
            logger.info(" new shot file: %s", newshotfile)
            with file(newshotfile, 'w') as new_fd:
                old_fd = file(shotfile,'r')
                new_fd.write(old_fd.read())
                new_fd.flush()
                old_fd.close()

            n_dna_shot_pairs.update({vdnafile: newshotfile})

        return (0, n_dna_shot_pairs)

    def generate_tasks(self):
        # get dna files
        # invoke this every time generate task jobs
        self.ltime = int(time.time())
        t1 = self.ltime - self.task_duration * (self.task_len + 1)
        t2 = self.ltime - self.task_duration * (self.task_len + 2)

        t1 *= 1000
        t2 *= 1000
        files = os.listdir(self.dna_dir)
        self.shotfiles = [x for x in files if x[-3:] == 'xml' and x.split('.')[0] == self.channel_id and int(x.split('.')[1]) / 1000 * 1000 > t1]
        self.shotfiles.sort()
        self.shotfiles = self.shotfiles[0:self.task_len]
        self.dnafiles = [x for x in files if x[-3:] == 'dna' and x.split('.')[0] == self.channel_id and int(x.split('.')[1]) * 1000 > t2]
        self.dnafiles.sort()
        self.dnafiles = self.dnafiles[0:self.task_len + 1]

        add_path = lambda x: os.path.normpath(os.path.join(self.dna_dir, x))
        self.shotfiles = map(add_path, self.shotfiles)
        self.dnafiles = map(add_path, self.dnafiles)
        logger.info("shotfiles: %s", str(self.shotfiles))
        logger.info("dnafiles: %s", str(self.dnafiles))
        dna_pairs = [{self.dnafiles[i]:self.dnafiles[i+1]} for i in xrange(len(self.dnafiles) -1)]

        if len(self.shotfiles) != len(dna_pairs):
            logger.error("shot files and dna pairs not matched!!")
            return -1
        try:
            dna_shot_pairs = dict(zip(self.shotfiles, dna_pairs))
            ret, n_dsp = self.dna_shot_merge(dna_shot_pairs)
            if ret != 0 or n_dsp is None:
                logger.error("map dna and shot file failed ret %d", ret)
                return -1
            for dnaf, shotf in n_dsp.iteritems():
                shot_file = shotf.split(os.sep)[-1]
                dna_file = dnaf.split(os.sep)[-1]
                start_ts = int(dna_file.split('.')[1])
                end_ts = int(dna_file.split('.')[2])
                task_file_tgz = dna_file[0:-4] + "tgz"
                cmd = "cd %s; tar czf %s %s %s; rm -f %s %s" % ( self.down_dir, task_file_tgz, shot_file, dna_file, shot_file, dna_file)
                logger.info("cmd is %s", cmd)
                r = os.system(cmd)
                if r != 0:
                    logger.error("compress dna file failed, result is %d", r)
                
                d = {}
                download_url = "".join((self.download_prex, '/', task_file_tgz))
                d.update({'beginTimestamp': start_ts})
                d.update({'endTimestamp': end_ts})
                d.update({'beginTimestampOfDNA': 0})
                d.update({'downloadUrl': download_url})
                self.taskDNA.append(d)
        except Exception, err:
            logger.error("generate tasks faile: %s", err)
                
        
    def send_to_jobtracker(self):
        ret = -1
        url = self.jobtrackerurl

        # construct post data
        request_id = str(uuid.uuid4())
        # FIXME 
        videoManagerUrl = self.vmurl
        mainCapture = "true"
        timezone = time.tzname[0] 

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
                    "beginTimestamp": self.dna_begin_ts, \
                    "endTimestamp": self.dna_end_ts, \
                    "duration": self.dna_end_ts - self.dna_begin_ts, \
                    "taskDNA": self.taskDNA
                    }

        post_data = simplejson.dumps(post_info)

        logger.info("post data is: %s", post_data)
        try:
            headers = {"Content-Type": "application/json"}
            http = httplib2.Http(disable_ssl_certificate_validation = True)
            xml_stream = ""
            response = lambda: None
            response.status = 0
            response, xml_stream = http.request(url, "POST", headers = headers, body=post_data)
            if response and response.status == 200:
                logger.info("xml stream is : %s", xml_stream)
                ret = 0
                logger.info("send task to job tracker success: %d", response.status)
            else:
                logger.info("send task to job tracker failed, status: %d", response.status)
                ret = response.status

        except Exception, err:
            logger.error("send task to task job tracker failed: %s", err)
            logger.error("%s:", str(traceback.format_exc()))
        return ret

    def run(self):
        self.load_conf()
        self.generate_tasks()
        self.send_to_jobtracker()

class task_manager():
    """
    
    """
    def __init__(self):
        self.channel_infos = {}
        self.db_host = None
        self.db_name = None
        self.db_user = None
        self.db_pass = None
        self.db_inst = None


    def load_db_conf(self):
        path = "/opt/rtfp/etc/database.conf"
        config = ConfigParser.ConfigParser ()
        config.read (path)
        self.db_host = config.get("Database", "host")
        self.db_name = config.get("Database", "name")
        self.db_user = config.get("Database", "user")
        self.db_pass = config.get("Database", "passwd")
        if self.db_name != "":
            return 0
        return -1
    def new_mysql_conn(self):
        try:
            conn = torndb.Connection(self.db_host, self.db_name, \
                    user = self.db_user, password = self.db_pass)
        except Exception, err:
            logger.error("connect mysql error: %s", err)
        if conn != None:
            return conn


    def get_task_uuid(self):
        sql = "select id, channel_uuid, channel_name, dma, network from videoSource where is_using = 'true' "
        try:
            conn = self.new_mysql_conn()
            id_uuids = conn.query(sql)
            for item in id_uuids:
                if item.id and item.channel_uuid:
                    channel_id = item.id
                    channel_info = []
                    channel_info.append(item.channel_uuid)
                    channel_info.append(item.channel_name)
                    channel_info.append(item.dma)
                    channel_info.append(item.network)
                    self.channel_infos.update({channel_id: channel_info})
            conn.close()
        except Exception, err:
            logger.error("get channelid and channel_uuid failed: %s", err)

    def start_task_manager(self):
        self.load_db_conf()
        self.get_task_uuid()
        try:
            for channel_id, channel_info in self.channel_infos.iteritems():
                channel_uuid = channel_info[0]
                channel_name = channel_info[1]
                dma = channel_info[2]
                network = channel_info[3] 
                g = task_generator(str(channel_id), channel_uuid, channel_name, dma, network)
                g.start()
        except Exception, err:
            logger.error(" errror in start task manager: %s" , err)

if __name__ == "__main__":
    install_logger()
    lock_handler = lock_and_write_pid(lock_file, pid_file)
    logger.info('start ..')
    t = task_manager()
    #t.start_task_manager()
    sched = Scheduler(daemonic = False)
    sched.add_cron_job(t.start_task_manager, hour = '*/6', minute = '12')
    sched.start()
    logger.info('end ...')
    lock_handler.close()

