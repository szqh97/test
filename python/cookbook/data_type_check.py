#!/usr/bin/env python
# -*- coding: utf-8 -*-


class Descriptor:
    def __init__(self, name=None, **opts):
        self.name = name

        for key, value in opts.items():
            setattr(self, key, value)

        def __set__(self, instance, value):
            instance.__dict__[self.name] = value
