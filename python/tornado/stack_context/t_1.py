# -*- coding: utf-8 -*-

import tornado.ioloop
IL = tornado.ioloop.IOLoop.instance()


def callback():
    try:
        raise Exception, 'in callback'
    except:
        print 'callback ok'

def like_other(func):
    def wrapper(*args, **kwarg):
        try:
            func(*args, **kwarg)
        except:
            print 'like_other ok'
    return wrapper
def func():
    #IL.add_callback(callback)
    IL.add_callback(like_other(callback))

def out():
    try:
        func()
    except:
        print 'ok'

out()
IL.start()
