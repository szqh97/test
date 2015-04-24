# -*- coding: utf-8 -*-

import tornado.ioloop
IL = tornado.ioloop.IOLoop.instance()

def callback():
    raise Exception, 'in callback'

def func():
    IL.add_callback(lambda: env(callback))

def env(func):
    try:
        func()
    except:
        print 'ok'

def out():
    env(func)

out()
IL.start()

