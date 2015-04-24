# -*- coding: utf-8 -*-

import tornado.ioloop
IL = tornado.ioloop.IOLoop.instance()


def callback():
    raise Exception, 'in callback'

def func():
    IL.add_callback(callback)

def out():
    try:
        func()
    except:
        print 'ok'

out()
IL.start()

import contextlib

