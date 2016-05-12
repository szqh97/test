#!/usr/bin/env python
# -*- coding: utf-8 -*-
def appendtest(newitem, lista=[]):
    print id(lista)
    lista.append(newitem)
    print id(lista)
    return lista
#print appendtest('a', ['b', 2, 4, [1,2]])

print appendtest(1)
print appendtest('a')

