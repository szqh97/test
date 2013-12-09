#!/usr/bin/env python
# -*- coding: utf8 -*-
# Author: li_yun@vobile.cn
# Date:  2013-12-09 10:08:05

import os
import time
import struct
import collections
import xml.dom.minidom

class task_generator():
    """ 
    generate task for TV Ads Job tracker
    """
    def __init__(self, len):
        self.task_len = 6 #the task cycle time (hour)
        self.redunt_time = 60 #the redundancy time (second)
        self.shotfiles = collections.deque()
        self.dnafiles = collections.deque()
        self.dna_dir = '/opt/rtfp/var/cache/dna_dir/'
        self.ltime = None
        self.dna_fd = None
        self.channel_id = None
        self.new_dna_file = ""

    def load_conf(self):
        self.dna_dir = '/opt/rtfp/var/cache/dna_dir/'
        pass

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
                        new_dna_file = self.channel_id + "." + str(vdna_begin_ts) 
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


    def merge_shot_info_by_files(self, prev_shot_file, curt_shot_file, next_shot_file):
        prev_dom = parse(prev_shot_file)
        shot_nodes = prev_dom.getElementsByTagName('shot')
        new_start_ts = (3600 - self.redunt_time) * 1000
        for shot in shot_nodes:
            start_ts = int(shot.getElementsByTagName('shot')[0].firstchild.data)
            if start_ts >= new_start_ts:
                #TODO
            



                
