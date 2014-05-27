#!/usr/bin/env python
import time
class Subject(object):
    def __init__(self):
        self.observers = []
        self.cur_time = None
    def register_observer(self, observer):
        if observer in self.observers:
            print observer, 'already in subscribed observers'
        else:
            self.observers.append(observer)
    
    def unregister_observer(self, observer):
        try: 
            self.observers.remove(observer)
        except ValueError:
            print 'No such observer in subject'

    def notify_observers(self):
        self.cur_time = time.time()
        for observer in self.observers:
            observer.notify(self.cur_time)

from abc import ABCMeta, abstractmethod
import datetime

class Observer(object):
    """ Abstract class for observers, provides notify method as
    interface for subjects."""
    __metaclass__ = ABCMeta

    @abstractmethod
    def notify(self, unxi_timestamp):
        pass

class USATimeObserver(Observer):
    def __init__(self, name):
        self.name = name
    def notify(self, unix_timestamp):
        time = datetime.datetime.fromtimestamp(int(unix_timestamp)).strftime('%Y-%m-%d %I:%M:%S %P')
        print 'Observer', self.name, "say: ", time

class EUTimeObserver(Observer):
    def __init__(self, name):
        self.name = name
    def notify(self, unix_timestamp):
        time = datetime.datetime.fromtimestamp(int(unix_timestamp)).strftime('%Y-%m-%d %H:%M:%S')
        print 'Observer', self.name, "say:", time

if __name__ == '__main__':
    subject = Subject()
    
    print "Adding usa_time"
    obs1 = USATimeObserver('usa_time')
    subject.register_observer(obs1)
    subject.notify_observers()

    time.sleep(2)
    print 'Adding eu_time'
    obs2 = EUTimeObserver('eu_time')
    subject.register_observer(obs2)
    subject.notify_observers()

    time.sleep(2)
    print 'Removing usa_time'
    subject.unregister_observer(obs1)
    subject.notify_observers()

