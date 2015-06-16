#!/usr/bin/env python
import sys
for yuvfile in sys.argv[1:]:
    begin_time = int(yuvfile.split('.')[0])
    end_time = int(yuvfile.split('.')[1])
    print yuvfile, end_time-begin_time
