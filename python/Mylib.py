#!/usr/bin/env python
class MyIterator(object):

    def __init__(self, step):
        self.step = step
    def next(self):
        """Returns the next elements"""
        if self.step == 0:
            raise StopIteration
        self.step -= 1
    def __iter__(self):
        """"""
        return self
