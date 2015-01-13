import time
from tornado.ioloop import IOLoop
from tornado import gen

def my_function(callback):
    print 'do some work'
    time.sleep(1)
    callback(123)

@gen.engine
def f():
    print 'start'
    result = yield gen.Task(my_function)
    print 'result is ', result
    IOLoop.instance().stop;

if __name__ == '__main__':
    f();
    IOLoop.instance().start()
