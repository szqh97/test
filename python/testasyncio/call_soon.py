#!/usr/bin/env python
# -*- coding: utf-8 -*-
import asyncio
import functools

def callback(arg, *, kwarg = 'default'):
    print ('callback invoked with {} and {}'.format(arg, kwarg))

async def main(loop):
    print("registering callback")
    loop.call_soon(callback, 1)
    wrapped = functools.partial(callback, kwarg = "no default")
    await asyncio.sleep(1)
    loop.call_soon(wrapped, 2)

event_loop = asyncio.get_event_loop()
try:
    print ("entering")
    event_loop.run_until_complete(main(event_loop))
finally:
    print("closing")
    event_loop.close()
