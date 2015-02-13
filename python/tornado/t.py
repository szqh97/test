from tornado import gen
from tornado.ioloop import IOLoop

@gen.coroutine
def throw():
    10/0 # Exception here
    return 'hello'


@gen.coroutine
def test():
    print "i'm ok"
    try:
        res = yield gen.Task(throw)
    except Exception, e:
        print e
    print "here too" # it is never executed


test()

IOLoop.instance().start()
