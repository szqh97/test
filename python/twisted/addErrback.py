#!/usr/bin/env pyhon
from twisted.internet.defer import Deferred
def myCallback(result):
    print result
d = Deferred()
d.addErrback(myCallback)
d.errback("Triggering callback")
