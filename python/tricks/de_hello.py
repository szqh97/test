#!/usr/bin/env python
# -*- coding: utf-8 -*-
def trace(fn):
    def wrapper():
        print 'entring, {}'.format(fn.__name__)
        fn()
        print 'leaving, {}'.format(fn.__name__)
    return wrapper

@trace
def foo():
    print 'I am doing...'
foo()
