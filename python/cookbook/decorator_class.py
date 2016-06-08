#!/usr/bin/env python
# -*- coding: utf-8 -*-

from functools import wraps
class A:
    def decorator1(self, func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            return func(*args, **kwargs)
        return wrapper

    @classmethod
    def decorator2(cls, func):
        @wraps(func)
        def wrapper(*args, **kwargs):
            print ('Decorator2')
            return func(*args, **kwargs)
        return wrapper
