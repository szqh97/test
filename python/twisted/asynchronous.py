#!/usr/bin/env python
from twisted.internet import reactor, defer

class HeadlineRetriever(object):
    def processHeadline(self, headline):
        if len(headline) > 50:
            self.d.errorback("The headline ``%s'' is too long!" % (headline, ))
        else:
            self.d.callback(headline)
    
    def _toHTML(self, result):
        return "<h1>%s</h1>" %(result, )
    
    def getHeadline(self, input):
        self.d = defer.Deferred()
        reactor.callLater(1, self.processHeadline, input)
        self.d.addCallback(self._toHTML)
        return self.d

def printData(result):
    print result
    reactor.stop()

def printError(failuer):
    print failuer
    reactor.stop()

h = HeadlineRetriever()
d = h.getHeadline("Breaking News: Twisted takes us to the Moon!")
#d = h.getHeadline("1234567890" * 6)
d.addCallbacks(printData, printError)
reactor.run()
