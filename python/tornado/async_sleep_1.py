import time
from tornado.ioloop import IOLoop
from tornado import gen

@gen.engine
def f():
    print 'sleeping...'
    yield gen.Task(IOLoop.instance().add_timeout, time.time() + 1)
    print 'awake'

if __name__ == '__main__':
    IOLoop.instance().add_callback(f)
    IOLoop.instance().add_callback(f)
    IOLoop.instance().start()
    IOLoop.instance().stop()
    
