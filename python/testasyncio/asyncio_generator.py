#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio

@asyncio.coroutine
def outer():
    print ("in outer")
    result1 = yield from phase1()
    result2 = yield from phase2()
    return (result1, result2)

@asyncio.coroutine
def phase1():
    print ("in phase1")
    return "result1"

@asyncio.coroutine
def phase2():
    print ("in phase2")
    return "result2"

event_loop = asyncio.get_event_loop()
try:
    ret_value = event_loop.run_until_complete(outer())
    print(ret_value)
except Exception as e:
    raise e
finally:
    event_loop.close()
