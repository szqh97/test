def falldow():
    raise Exception("fall down")
def upagain():
    print "up again"
    reactor.stop()

from twisted.internet import reactor
reactor.callWhenRunning(falldow)
reactor.callWhenRunning(upagain)


reactor.run()
