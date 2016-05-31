#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time
class Date:
    __slots__ = ['year', 'month', 'day']
    def __init__(self, year, month, day):
        self.year = year
        self.month = month
        self.day = day

dates = []
for i in xrange(10000000):
    dates.append(Date(1,1,1))

time.sleep(100)

