# -*- coding: utf-8 -*-

import tornado.ioloop
IL = tornado.ioloop.IOLoop.instance()

class Context(object):
    def __enter__(self):
        return 123
    def __exit__(self, type, value, tracback):
        return True

with Context() as i:
    print i
    raise Exception, 1
