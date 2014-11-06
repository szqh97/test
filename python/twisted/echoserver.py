#!/usr/bin/env python
from twisted.internet import protocol, reactor
class Echo(protocol.Protocol):
    def __init__(self):
        pass
    def connectionMade(self):
        global count 
        count += 1
        print "a connection is made, all is : ", count, ": alive is: ", self.connected, ":"

    def dataReceived(self, data):
        self.transport.write(data)

    def connectionLost(self, reason):
        print reason
        pass

class EchoFactory(protocol.Factory):
    def buildProtocol(self, addr):
        #print 'port is :', self.numPorts
        print addr
        return Echo()

    def startFactory(self):
        return Echo()

count = 0
reactor.listenTCP(8000, EchoFactory())
reactor.run()
