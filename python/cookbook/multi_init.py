#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time

class Date:
    def __init__(self, y, m, d):
        self.year = y
        self.month = m
        self.day = d

    @clasmethod
    def today(cls):
        t = time.localtime()
        return cls(t.tm_year, t.tm_mon, t.tm_mday)
