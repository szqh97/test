#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio
import functools
import time

def callback(n):
    print ('callback {} invoked at {}'.format(n, time.time()))

async def main(loop):
    print("registering callback")
    loop.call_later(5, callback, 1)
    loop.call_later(2, callback, 2)
    loop.call_soon(callback, 3)
    await asyncio.sleep(10)

event_loop = asyncio.get_event_loop()
try:
    print ("entering")
    event_loop.run_until_complete(main(event_loop))
finally:
    print("closing")
    event_loop.close()
