#!/usr/bin/env python
# -*- coding: utf-8 -*-
def change_list(orginator_list):
    print 'orgnator_list is:', orgnator_list
    new_list = orgnator_list
    new_list.append('I am new')
    print 'new list is :', new_list
    return new_list

orgnator_list = ['a', 'b', 'c']
new_list = change_list(orgnator_list)
print new_list
print orgnator_list

print '=========================='

def change_me(org_list):
    print id(org_list)
    new_list = org_list
    print id(new_list)
    if len(new_list) > 5:
        new_list = ['a', 'b', 'c']
    for i, e in enumerate(new_list):
        if isinstance(e, list):
            new_list[i] = '***'
    print new_list
    print id(new_list)

test1 = [1, ['a', 1, 3], [2, 1], 6]
print test1
change_me(test1)
print test1

print '......'

test2 = [1, 2, 3, 4, 5, [1, 2], 6 ]
print test2
change_me(test2)
print test2

