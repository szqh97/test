#!/usr/bin/env pyhon
from twisted.internet.defer import Deferred
def myCallback(result):
    print 'xxxx'
    print result
d = Deferred()
d.addCallback(myCallback)
d.callback("Triggering callback")
