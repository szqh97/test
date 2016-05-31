#!/usr/bin/env python
# -*- coding: utf-8 -*-
class Person:
    def __init__(self, first_name):
        self.first_name = first_name

    @property
    def first_name(self):
        return self._first_name

    @first_name.setter
    def first_name(self, value):
        if not isinstance(value, str):
            raise TypeError('Excepted string')
        self._first_name = value

    @first_name.deleter
    def first_name(self):
        raise AttributeError("Can't delte attribute")

class Person2:
    def __init__(self, first_name):
        self.set_first_name(first_name)

    def get_first_name(self):
        return self._first_name

    def set_first_name(self, value):
        if not isinstance(value, str):
            raise TypeError('Expected a string')
        self._first_name = value

    def del_first_name(self):
        raise AttributeError("can't delete attribute")

    name = property(get_first_name, set_first_name, del_first_name)
