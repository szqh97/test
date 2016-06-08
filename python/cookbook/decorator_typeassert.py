#!/usr/bin/env python
# -*- coding: utf-8 -*-
from inspect import signature
from functools import wraps

def typeassert(*ty_args, **ty_kwargs):
    def decorate(func):
        if not __debug__:
            return func

        sig = signature(func)
        bound_tyes = sig.bind_partial(*ty_args, **ty_kwargs).arguments

        @wraps(func)
        def wrapper(*args, **kwargs):
            bound_values = sig.bind(*args, **kwargs)
            for name, value in bound_values.arguments.items():
                if name in bound_tyes:
                    if not isinstance(value, bound_tyes[name]):
                        raise TypeError('Argument {} must be {}'.format(name, bound_tyes[name]))
            return func(*args, **kwargs)

        return wrapper
    return decorate
