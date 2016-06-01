#!/usr/bin/env python
# -*- coding: utf-8 -*-


class Structure2:
    _fields = []

    def __init__(self, *args, **kwargs):
        if len(args) > len(self._fields):
            raise TypeError('Expected {} arguments'.format(len(self._fields)))

        for name, value in zip(self._fields, args):
            setattr(self, name, value)

        for name in self._fields[len(args):]:
            setattr(self, name, kwargs.pop(name))

        if kwargs:
            raise TypeError('Invalid argument(s): {}'.format('.'.join(kwargs)))

if __name__ == '__main__':

    class Stock(Structure2):
        _fields = ['name', 'shares', 'prices']

    s1 = Stock('ACME', 50, 90.1)
    s2 = Stock('ACME', 50, prices=0.1)
    s3 = Stock('ACME', shares=50, prics=0.1)
