#!/usr/bin/env python
# -*- coding: utf8 -*-
# get every frame's ts info from dna 
# by li_yun@163.com 2014-02-11 15:35:35
#
import sys
import os
import struct

CB_LEN = 24
DNA_FRAME_LEN = 40
DNA_HEAD_LEN = 48


def parse_ts (cdnafile):
    f = file(cdnafile, 'r')
    f.seek(CB_LEN + DNA_HEAD_LEN)
    cb = f.read(CB_LEN)
    cb_h = struct.unpack("4iq", cb)
    while cb_h[2] != 0:
        dnas = f.read(cb_h[2])
        while len(dnas) != 0:
            dna = dnas[0:40]
            dnas = dnas[40:]
            print struct.unpack('I', dna[0:4])[0]
        cb = f.read(CB_LEN)
        cb_h = struct.unpack("4iq", cb)

if __name__ == "__main__":
    dnafile = sys.argv[1]
    parse_ts(dnafile)


