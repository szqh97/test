#!/usr/bin/env python
# -*- coding: utf-8 -*-
import copy
class Pizza(object):
    def __init__(self, name, size, price):
        self.name = name
        self.size = size
        self.price = price

    def getPizzaInfo(self):
        return self.name, self.size, self.price

    def showPizzaInfo(self):
        print '    pizza name: {}'.format(self.name)
        print '    pizza size: {}'.format(self.size)
        print '    pizza price: {}'.format(self.price)
        print '    ....'

    def changeSize(self, size):
        self.size = size

    def changePrice(self, price):
        self.price = price

class Order(object):
    def __init__(self, name):
        self.customernam = name
        self.pizzaList = []
        self.pizzaList.append(Pizza("Mushroom", 12, 30))

    def ordermore(self, pizza):
        self.pizzaList.append(pizza)

    def changeName(self, name):
        self.customernam = name

    def getorderdetail(self):
        print 'customer name: {}'.format(self.customernam)
        for pizza in self.pizzaList:
            pizza.showPizzaInfo()
    
    def getPizza(self, number):
        print 'xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx', number
        print list(self.pizzaList)
        print len(self.pizzaList)
        return self.pizzaList[number]

custormer1 = Order('zhang')
custormer1.ordermore(Pizza('seafood', 9, 40))
custormer1.ordermore(Pizza('fruit', 10, 32))
print 'custormer1 order infomation:'
custormer1.getorderdetail()
print len(custormer1.pizzaList)
print '----------------------------------'


custormer2 = copy.deepcopy(custormer1)
print 'order 2 customer name: {}'.format(custormer2.customernam)
custormer2.changeName('Li')
custormer2.getPizza(2).changeSize(9)
custormer2.getPizza(2).changePrice(30)
print 'custormer2 order infomation: '
custormer2.getorderdetail()
print '----------------------------------'

print 'costomer1 order information'
custormer1.getorderdetail()
