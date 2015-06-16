#!/usr/bin/env python
# -*- ccoding: utf8 -*-

# author: li_yun@163.com
# date: 2013-12-08 14:24:44
import struct
import sys

dnafile = '2.1386376200.cdna'

def generate_dna_info(dnafile):
    f = file(dnafile, 'r')
    head = f.read(24)
    h = struct.unpack('4iq', head)
    while h[2] != 0:
        print "====" + str(h[4])
        dna_buf = f.read(h[2])
        i = 0
        while len(dna_buf) != 0:
            dna_frame = dna_buf[0:40]
            dna_buf = dna_buf[40:]
            dna = struct.unpack('I36B', dna_frame)
            print h[4]+i*40, dna[0]
            i += 1
        head = f.read(24)
        h = struct.unpack('4iq', head)

if __name__ == '__main__':
    generate_dna_info(sys.argv[1])



    

