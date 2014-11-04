#!/usr/bin/env python
from twisted.internet.protocol import Protocol, Factory
from twisted.internet import reactor

class Echo(Protocol):
    def connectioniMade(self):
        self.factory.numProtocols = self.factory.numProtocols + 1
        if self.factory.numProtocols > 100:
            self.transport.write("too many connections, try later")
            self.transport.loseConnection()

    def connectionLost(self, reason):
        self.factory.numProtocols = self.factory.numProtocols - 1

    def dataReceived(self, data):
        self.transport.write(data)

class QOTD(Protocol):

    def connectioniMade(self):
        self.transport.write("An apple a day keeps doctor away\r\n")
        self.transport.loseConnection()

from twisted.protocols.basic import LineReceiver
class Answer(LineReceiver):
    answers = {'How are you?': 'Fine', None: 'I dont what you mean'}
    def lineReceived(self, line):
        if self.answers.has_key(line):
            self.sendLine(self.answers[Line])
        else:
            self.sendLine(self.answers[None])


factory = Factory()
factory.protocol = QOTD

reactor.listenTCP(8007, factory)
reactor.run()


