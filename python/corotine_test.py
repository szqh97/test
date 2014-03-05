#!/usr/bine/env python
import time
import multitask
def f1():
    for i in xrange(4):
        print "f1", i
        yield None
        time.sleep(1)

def f2():
    for i in xrange(4):
        print "f2", i
        yield None
        time.sleep(2)

multitask.add(f1())
multitask.add(f2())
multitask.run()

