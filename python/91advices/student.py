#!/usr/bin/env python
"""
"""
# -*- coding: utf-8 -*-


class Student(object):
    def __init__(self, name, course=None):
        if course is None:
            course = []
        self.name = name
        self.course = course

    def addcourse(self, coursename):
        self.course.append(coursename)

    def printcourse(self):
        for item in self.course:
            print item

stuA = Student('Want Yi')
stuA.addcourse('Englist')
stuA.addcourse('Math')
print '{name}\'s course:'.format(name=stuA.name)
stuA.printcourse()
print '-------------------------'

stuB = Student('Li San')
stuB.addcourse('Chinese')
stuB.addcourse('Physics')
print '{name}\'s course:'.format(name=stuB.name)
stuB.printcourse()
print '-------------------------'
