#!/usr/bin/env python
# -*- coding: utf-8 -*-
class Base:
    def __init__(self):
        print ('Base.__init__')

class A(Base):
    def __init__(self):
        Base.__init__(self)
        print ('A.__init__')

class B(Base):
    def __init__(self):
        Base.__init__(self)
        print ('B.__init__')

class C(A, B):
    def __init__(self):
        A.__init__(self)
        B.__init__(self)
        print('C.__init__')
