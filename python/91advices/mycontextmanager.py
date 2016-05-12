#!/usr/bin/env python
# -*- coding: utf-8 -*-
class MyContextManager(object):
    def __enter__(self):
        print 'entering...'
    def __exit__(self, exception_type, exception_value, traceback):
        print 'leaving...'
        if exception_type is None:
            print 'no exception'
            return False
        elif exception_type is ValueError:
            print 'Value Error !!!'
            return True
        else:
            print 'Other Error !!'
            return True

with MyContextManager():
    print 'Testing ...'
    raise (ValueError)
