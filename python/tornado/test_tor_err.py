#!/usr/bin/env python
from tornado.gen import coroutine
from tornado.ioloop import IOLoop
from tornado import stack_context

import contextlib

@contextlib.contextmanager
def die_on_error():
    try:
        1/0
    except Exception :
        print "eeeeee"

with stack_context.StackContext(die_on_error) as cb:
    print 'a'

IOLoop.start()
