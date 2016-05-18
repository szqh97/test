#!/usr/bin/env python
# -*- coding: utf-8 -*-

class A(object):
    def instance_method(self, x):
        print 'calling instance method instance_method({0}, {1})'.format(self, x)

    @classmethod
    def class_method(cls, x):
        print 'calling class_method ({0}, {1})'.format(cls, x)

    @staticmethod
    def static_method(x):
        print 'calling static_method ({})'.format(x)

a = A()
a.instance_method('test')
a.class_method('test')
a.static_method('test')


class Fruit(object):
    total = 0
    @classmethod
    def print_total(cls):
        print cls.total
        print 'class is {}'.format(cls)
        print id(Fruit.total)
        print id(cls.total)

    @classmethod
    def set(cls, value):
        print 'calling class_method ({0}, {1})'.format(cls, value)
        cls.total = value

class Apple(Fruit):
    pass

class Orange(Fruit):
    pass


app1 = Apple()
app1.set(200)
app2 = Apple()
org1 = Orange()
org1.set(300)
org2 = Orange()

app1.print_total()
org1.print_total()
