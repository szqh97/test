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
        
        for i in xrange(100):
            self.digits.append(random.random())

    def sort(self, reverse = False):
        if reverse:
            self.digits.reverse()

class Proxy(AbstractSubject):
    """ A proxy which creates an object if it is not exist and 
    caches it otherwise."""

    def __init__(self):
        """ A constructor which creates an object if it is not exist and """
        if not getattr(self.__class__, "cached_object", None):
            self.__class__.cached_object = RealSubject()
            self.__class__.reference_count = 1
            print "Created new object"
        else:
            print "Using cached object"
            self.__class__.reference_count += 1
        print 'Count of reference = ', self.__class__.reference_count
    def sort(self, reverse = False):
        """ THe args are logged by the Proxy."""
        print "Called sort method with args:"
        print locals().items()
        self.__class__.cached_object.sort(reverse = reverse)
    def __del__(self):
        """ Decreases a reference to an object. if the number of
        references is 0, delte the object."""
        self.__class__.reference_count -= 1
        if self.__class__.reference_count == 0:
            print "Number of reference_count is 0, Deleting cached objec ..."
            del self.__class__.cached_object
        print 'Deleted object count of object = ', self.__class__.reference_count

if __name__ == '__main__':
    p1 = Proxy()

    p2 = Proxy()

    p3 = Proxy()

    p1.sort(True)

    del p2
