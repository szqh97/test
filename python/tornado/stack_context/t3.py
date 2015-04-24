
# -*- coding: utf-8 -*-

import tornado.ioloop
IL = tornado.ioloop.IOLoop.instance()

def callback():
    raise Exception, 'in callback'

HOLE = {}

def func():
    IL.add_callback(lambda: HOLE[''](callback))

def env (func):
    try:
        func()
    except:
        print 'ok'

def out():
    HOLE.setdefault('', env)(func)

out()
IL.start()
