#!/usr/bin/env python
import threading
import multiprocessing
import time

def cpu_():
    while True:
        pass

t = multiprocessing.Process(target=cpu_)
t.start()
print 'aaaaaaaaaaa'
time.sleep(30)
t.terminate()
time.sleep(10)
print 'exit'
