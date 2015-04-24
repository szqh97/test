#!/usr/bin/env python
from optparse import OptionParser
if __name__ =='__main__':


    parse = OptionParser()
    parse.add_option("-f", "--file", dest = "filename", help = "file name ")
    parse.add_option("-q", '--quit', dest = 'verbose', help = 'quit the app')
    option, args = parse.parse_args()
    print option
    print args
