#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio

async def outer():
    print ("in outer")
    result1 = await phase1()
    result2 = await phase2()
    return (result1, result2)

async def phase1():
    print ("in phase1")
    return "result1"

async def phase2():
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
