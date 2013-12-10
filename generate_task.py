#!/usr/bin/env python
# -*- coding: utf8 -*-
# Author: li_yun@vobile.cn
# Date:  2013-12-09 10:08:05

import os
import time
import struct
import logging
import threading
import traceback
import collections
import xml.dom.minidom
from xml.dom.minidom import parse, parseString

class task_generator(threading.Thread):
    """ 
    generate task for TV Ads Job tracker
    """
    def __init__(self, channel_id ):
        threading.__init__(self)
        self.task_len = 6 #the task cycle time (hour)
        self.redunt_time = 60 #the redundancy time (second)
        self.shotfiles = collections.deque()
        self.dnafiles = collections.deque()
        self.dna_dir = '/opt/rtfp/var/cache/dna_dir/'
        self.ltime = None
        self.dna_fd = None
        self.channel_id = None
        self.new_dna_file = ""
        self.channel_uuid = channel_id
        self.db_host = None
        self.db_name = None
        self.db_user = None
        self.db_pass = None


    def load_conf(self):
        self.load_db_conf()
        self.dna_dir = '/opt/rtfp/var/cache/dna_dir/'
        pass

    def load_db_conf(self):
        path = "./etc/database.conf"
        config = ConfigParser ()
        config.read (path)
        self.db_host = config.get("Database", "host")
        self.db_name = config.get("Database", "name")
        self.db_user = config.get("Database", "user")
        self.db_pass = config.get("Database", "passwd")
        if self.db_name != "":
            return 0
        return -1


    def getfiles(self):
        # get dna files
        # invoke this every time generate task jobs
        self.ltime = time.time()
        t_begin_time = ltime - 3600 * (self.task_len + 1)
        for f in os.listdir(self.dna_dir):
            if int(ltime) - int(f[2:11]) < (self.task_len + 1 ) * 3600:
                if f[-3:] == 'xml': 
                    self.shotfiles.append(os.path.normpath(os.path.join(self.dna_dir, f)))
                elif f[-3:] == 'dna':
                    self.dnafiles.append(os.path.normpath(os.path.join(self.dna_dir, f)))

    def merge_vdna_by_file(self, prev_f, cur_f, nex_f):

        # struct dna_control_block
        # {
        #     int serial_number;
        #     int type;
        #     int length;
        #     int pad;
        #     long long timestamp;    // millisecond.
        # };

        vdna_buf = ""
        dna_fd = None
        rf = file(prev_f, "r")
        # TODO if the dna file is bad? raise exception
        rf.seek(-104, 2)
        last2_dna_frame = struct.unpack('I36B', rf.read(40))
        last2_frame_ts = last2_dna_frame[0]
        last_dna_frame = struct.unpack('I36B', rf.rad(40))
        last_frame_ts = last_dna_frame[0]
        d_ts = last_fram_ts - last2_frame_ts

        # 1.read prev dna file
        vdna_begin_ts = 0
        rf.seek(0)
        rh_buf = rf.read(24)
        rh = struct.unpack('3iq', rh_buf)
        frame_ts = 0
        while rh[2] != 0:
            dna_buf = rf.read(rh[2])
            while len(dna_buf) != 0:
                dna_frame_buf = dna_buf[0:40]
                dna_buf = dna_buf[40:]
                dna_frame_ts = struct.unpack('I', dna_frame_buf[0:4])[0]
                if dna_frame_ts + self.redunt_time * 1000 >= last_frame_ts:
                    vdna_begin_ts = h[4] + i * deltats
                    if dna_fd == None:
                        new_dna_file = self.channel_id + "." + str(vdna_begin_ts) \
                            + ".vdna"
                        dna_fd = file(os.path.normpath(os.path.join(self.dna_dir, 
                            self.new_dna_file, "w")))
                        frame_ts += deltats
                    dna_frame_buf = struct.pack('I', frame_ts) + dna_frame_buf[4:]
                    vdna_buf += dna_frame_buf
                    if len(vdna_buf) >= 40960:
                        dna_fd.write(vdna_buf)
                        vdna_buf = ""
            rh_buf = rf.read(24)
            rh = struct.unpack('3iq', rh_buf)
        dna_fd.write(vdna_buf)
        vdna_buf = ""
        rf.close()

        # 2. write curr dna file
        cf = file(cur_f, 'r')
        ch_buf = cf.read(24)
        ch = struct.unpack('3iq', ch_buf)
        while ch[2] != 0:
            dna_buf = cf.read(ch[2])
            while len(dna_buf) != 0:
                frame_ts += deltats
                dna_frame_buf = dna_buf[0:40]
                dna_buf = dna_buf[40:]
                dna_frame_buf = struct.pack('I', frame_ts) + dna_frame_buf[4:]
                vdna_buf += dna_frame_buf
                if len(vdna_buf) >= 40960:
                    dna_fd.write(vdna_buf)
                    vdna_buf = ""
            ch_buf = rf.read(24)
            ch = struct.unpack('3iq', ch_buf)
        dna_fd.write(vdna_buf)
        vdna_buf = ""
        cf.close()

        # 3.write next dna file
        nf = file(nex_f, 'r')
        nh_buf = nf.read(24)
        nh = struct.unpack('3iq', nh_buf)
        while nh[2] != 0:
            dna_buf = nf.read(ch[2])
            while len(dna_buf) != 0:
                frame_ts += deltats
                dna_frame_buf = dna_buf[0:40]
                dna_buf = dna_buf[40:]
                d = struct.unpack('I', dna_frame_buf[0:4])[0]
                if d <= self.redunt_time * 1000:
                    dna_frame_buf = struct.pack('I', frame_ts) + dna_frame_buf[4:]
                    vdna_buf += dna_frame_buf
                    if len(vdna_buf) > 40960:
                        dna_fd.write(vdna_buf)
                        vdna_buf = ""
            nh_buf = rf.read(24)
            ch = struct.unpack('3iq', ch_buf)
        dna_fd.write(vdna_buf)
        dna_fd.close()
        vdna_buf = ""
        nf.close()


    def merge_shot_info_by_files(self, prev_shot_file, curr_shot_file, next_shot_file):

        # prev_shot_file like: /opt/rtfp/var/cache/dna_dir/2.1386612900000.1386613200000.xml
        # curr_shot_file like: /opt/rtfp/var/cache/dna_dir/2.1386613200000.1386613500000.xml
        # next_shot_file like: /opt/rtfp/var/cache/dna_dir/2.1386613500000.1386613500000.xml

        str_shot_info ="<shots></shots>"
        shot_len = 0
        new_sf_dom = parseString(str_shot_info)
        try:
            # 1. get the reduntant shot info from prev_shot_file
            prev_dom = parse(prev_shot_file)

            shot_nodes = prev_dom.getElementsByTagName('shot')
            prev_start_ts = int(prev_shot_file.split(os.sep)[-1][2:15])
            prev_end_ts = int(prev_shot_file.split(os.sep)[-1][16:29])
            new_start_ts = prev_end_ts - self.redunt_time * 1000
            new_end_ts = -1
            for shot in shot_nodes:
                start_ts_n = shot.getElementsByTagName('start')[0].childNodes[0]
                start_ts = int(start_ts_n.nodeValue)
                end_ts_n = shot.getElementsByTagName('end')[0].childNodes[0] 
                end_ts = int(end_ts_n.nodeValue)
                if prev_start_ts + start_ts >= new_start_ts:
                    # start ts 
                    start_ts_n.nodeValue = str(prev_start_ts + start_ts - new_start_ts)
                    # end ts 
                    new_end_ts = prev_start_ts + end_ts - new_start_ts
                    end_ts_n.nodeValue = str(new_end_ts)

                    # mid-boundary
                    mid_boundaries = shot.getElementsByTagName('mid-boundary')
                    for mb in mid_boundaries:
                        prev_ts_n = mb.getElementsByTagName('prev_ts')[0].childNodes[0]
                        prev_ts = int(prev_ts_n.nodeValue)
                        prev_ts_n.nodeValue = str(prev_start_ts + prev_ts - new_start_ts)

                    new_sf_dom.getElementsByTagName('shots')[-1].appendChild(shot)

            # 2. get the current task shot info
            curr_dom = parse(curr_shot_file)
            shot_nodes = curr_dom.getElementsByTagName('shot')
            curr_start_ts = int(curr_shot_file.split(os.sep)[-1][2:15])
            for shot in shot_nodes:
                # start ts
                start_ts_n = shot.getElementsByTagName('start')[0].childNodes[0]
                start_ts = int(start_ts_n.nodeValue)
                start_ts_n.nodeValue = str(curr_start_ts + start_ts - new_start_ts)
                # end ts
                end_ts_n = shot.getElementsByTagName('end')[0].childNodes[0]
                end_ts = int(end_ts_n.nodeValue)
                end_ts_n.nodeValue = str(curr_start_ts + end_ts - new_start_ts)
                 
                shot_len += end_ts - start_ts

                # mid-boundary
                mid_boudaries = shot.getElementsByTagName('mid-boundary')
                for mb in mid_boudaries:
                    prev_ts_n = mb.getElementsByTagName('prev_ts')[0].childNodes[0]
                    prev_ts = int(prev_ts_n.nodeValue)
                    prev_ts_n.nodeValue = str(curr_start_ts + prev_ts - new_start_ts)

                new_sf_dom.getElementsByTagName('shots')[-1].appendChild(shot)

            # 3. get redunt shot from 
            next_dom = parse(next_shot_file)
            shot_nodes = next_dom.getElementsByTagName('shot')
            next_start_ts = int(next_shot_file.split(os.sep)[-1][2:15])
            for shot in shot_nodes:
                #start ts
                start_ts_n = shot.getElementsByTagName('start')[0].childNodes[0]
                start_ts = int(start_ts_n.nodeValue)
                if start_ts <= self.redunt_time * 1000:
                    start_ts_n.nodeValue = str(next_start_ts + start_ts - new_start_ts)
                    #end ts
                    end_ts_n = shot.getElementsByTagName('end')[0].childNodes[0]
                    end_ts_n.nodeValue = str(next_start_ts + end_ts - new_start_ts)
                    # mid-boudnary
                    mid_boundaries = shot.getElementsByTagName('mid-boundary')
                    for mb in mid_boundaries:
                        prev_ts_n = mb.getElementsByTagName('prev_ts')[0].childNodes[0]
                        prev_ts = int(prev_ts_n.nodeValue)
                        prev_ts_n.nodeValue = str(next_start_ts + prev_ts - new_start_ts)

                    new_sf_dom.getElementsByTagName('shots')[-1].appendChild(shot)
                else:
                    # TODO end time a frame later
                    new_end_ts = start_ts + next_start_ts
                    break
        except Exception, err:
            print "merge_shot_info err:" + str(err)
            print traceback.format_exc()
        # TODO new dna an shot save to a new directory?
        new_shot_file = self.dna_dir + os.sep + str(self.channel_id) + "." \
                        + str(new_start_ts) + "." + str(new_end_ts) + ".xml"

        with file(new_shot_file, 'w') as sf:
            sf.write(new_sf_dom.toprettyxml())

        return shot_len

class task_manager():
    """
    
    """
    def __init__(self)
    self.id_uuid_dict = {}
    self.db_host = None
    self.db_name = None
    self.db_user = None
    self.db_pass = None
    self.db_inst = None


    def load_db_conf(self):
        path = "./etc/database.conf"
        config = ConfigParser ()
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
            conn = torndb.Connection(self.db_host, self.db_name, user = self.db_user, password = self.db_pass)
        except Exception, err:
            print "connect mysql error: %s" % (str)
        if conn != None:
            return conn


    def get_task_uuid(self):
        sql = "select id, channel_uuid from videoSource where is_using = 'true' "
        try:
            id_
        




    

