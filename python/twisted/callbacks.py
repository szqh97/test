#!/usr/bin/env python
from twisted.internet.defer import Deferred

def callback1(result):
    print "Callback 1 said:", result
    return result

def callback2(result):
    print "Callback 2 said:", result
    return result

def callback3(result):
    print "Callback 3 said:", result
    raise Exception("Callback 3")

def errback1(failuer):
    print "Errback 1 had an error on", failuer
    return failuer

def errback2(failuer):
    raise Exception("Errback 2")

def errback3(failuer):
    print "Errback 3 took care of ", failuer
    return "Everything is fine now"


d = Deferred()
d.addCallback(callback1)
d.addCallback(callback2)
d.addCallback(callback3)
d.callback("Test")
