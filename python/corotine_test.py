#!/usr/bine/env python
import multitask
def f1():
    for i in xrange(4):
        print "f1", i
        yield None

def f2():
    for i in xrange(4):
        print "f2", i
        yield None

multitask.add(f1())
multitask.add(f2())
multitask.add(f1())
multitask.run()

