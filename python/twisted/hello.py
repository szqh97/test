import traceback 
def hello():
    print 'Hello from the reactor loop!'
    traceback.print_stack()


from twisted.internet import reactor
reactor.callWhenRunning(hello)
print 'starting the reactor'
reactor.run()
