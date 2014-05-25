from abc import ABCMeta, abstractmethod
import random

class AbstractSubject(object):
    """ Acommon interface for the real and proxy objects. """
    __metaclass__ = ABCMeta

    @abstractmethod
    def sort(self, reverse = False):
        pass

class RealSubject(AbstractSubject):
    """ A class  for a heavy object which taks a log of memory 
    space and taks some time  to instantiate. """
    
    def __init__(self):
        self.digits = []
        
        for i in xrange(10000000):
            self.digits.append(random.random())

    def sort(self, reverse = False):
        if reverse:
            self.digits.reverse()

class Proxy(AbstractSubject):
    """ A proxy which creates an 

