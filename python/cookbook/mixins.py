#!/usr/bin/env python
# -*- coding: utf-8 -*-


class LoggedMappingMixin:
    __slots__ = ()
    
    def __getitem__(self, key):
        print ('Getting ' + str(key))
        return super().__getitem__(key)

    def __setitem__(self, key, value):
        print ('Setting {} = {!r}'.format(key, value))
        return super().__setitem__(key, value)

    def __delitem__(self, key):
        print('Deleting ' + str(key))
        super().__delitem__(key)


class SetOnceMappingMixin:
    '''
    Only allow a key to be set once
    '''
    __slots__ = ()
    def __setitem__(self, key, value):
        if key in self:
            raise KeyError(str(key) + ' already set')
        return super().__setitem__(key, value)

class StringKeyMappingMixin:
    '''
    Restrict keys to strings only
    '''
    __slots__ = ()

    def __setitem__(self, key, value):
        if not isinstance(key, str):
            raise TypeError('Keys must be strings')
        return super().__setitem__(key, value)

class LoggedDict(LoggedMappingMixin, dict):
    pass

d = LoggedDict()
d['x'] = 23
print (d['x'])
del d['x']
