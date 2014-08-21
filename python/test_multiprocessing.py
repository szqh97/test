#!/usr/bin/env python
import os
import time
import multiprocessing

plist = []
def f(i):
    print "now is ", time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    time.sleep(i)
    print "after sleep is ", time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())

for i in xrange(5):
    p = multiprocessing.Process(target = f, args = (i,))
    p.daemon = True
    plist.append(p)

    p.start()

for p in plist:
    p.join()
    print p.is_alive()
    print 'xxxxx'

